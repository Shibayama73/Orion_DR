//**********************************//
//*	���@�O�FRankFileIO.cpp
//*	���@�e�F���ʃt�@�C���N���X
//*	���@�t�F2017.06.12
//* �X�V���F2017.06.12
//*	����ҁFN.Shibayama
//**********************************//

#include "RankFileIO.h"

#include "GameOver.h"
#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

#include "Game.h"
#include "pch.h"
#include <WICTextureLoader.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

const int MAX_RANK = 3;

//==================================//
//���e		�R���X�g���N�^
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
RankFileIO::RankFileIO()
{
	//	������
	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 60.0f;
	m_grpH = 80.0f;

	for (int i = 0; i < MAX_RANK; i++) {
		m_rank[i] = 0;
	}

	//	�`��ǂݍ���============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/result.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> number;
	DX::ThrowIfFailed(resource.As(&number));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC numDesc;
	number->GetDesc(&numDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = 0.0;
	m_origin.y = 0.0;

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

}

//==================================//
//���e		�f�X�g���N�^
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
RankFileIO::~RankFileIO()
{
}

//==================================//
//���e		�`��
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
void RankFileIO::Render(float posX, float posY)
{
	//	����
	for (int i = 0; i < MAX_RANK; i++)
	{
		DrawNum(posX, posY + (110 * i), m_rank[i]);
	}

}

//===============================================================================//
//���e		���ʂ̕`��
//����		�\���ʒuX���W(float x)�A�\���ʒuY���W(float y)�A�\�����鐔�l(int n)
//�߂�l	�Ȃ�
//===============================================================================//
void RankFileIO::DrawNum(float posX, float posY, int num)
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	int number = num;	//��Ɨp
	int i = 0;			//������

	RECT rect;

	if (number < 0)
	{
		rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
		m_spriteBatch->Draw(m_texture.Get(), Vector2(posX, posY), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));
	}
	else
	{
		while (number)
		{
			m_grpX = (number % 10) * m_grpW;
			rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
			m_spriteBatch->Draw(m_texture.Get(), Vector2((posX - i * m_grpW), posY), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

			number = number / 10;
			i++;
		}
	}

	m_spriteBatch->End();
}

//=====================================================//
//���e		�����L���O�f�[�^�t�@�C���̓Ǎ��݁E������
//����		�Ǎ���(0)�A������(1)
//�߂�l	����(0)�A�ُ�(1)
//=====================================================//
int RankFileIO::RankingDataFileIO(int io)
{
	char *Filename = "rank.txt";
	FILE *fp;

	//�Ǎ��݂̂Ƃ�
	if (io == 0)
	{
		fp = fopen(Filename, "r");
		//	�Ǎ��݂����s�����Ƃ�
		if (fp == NULL) {
			return 1;
		}

		//fgets(s, 100, fp);
		//	��s���Ǎ���
		for (int i = 0; i < MAX_RANK; i++) {
			fscanf(fp, "%d", &m_rank[i]);
		}
	}
	//�����݂̂Ƃ�
	else
	{
		fp = fopen(Filename, "w");
		//	�����݂����s�����Ƃ�
		if (fp == NULL) {
			return 1;
		}
		//	1�s��������
		for (int i = 0; i < MAX_RANK; i++) {
			fprintf(fp, "%d\n", m_rank[i]);
		}
	}
	fclose(fp);
	return 0;
}

//========================================//
//���e		�f�[�^���~���ɕ��ׂ�
//����		�Ȃ�
//�߂�l	�Ȃ�
//========================================//
void RankFileIO::SetRanking()
{
	//	���ʃt�@�C���̓Ǎ���
	this->RankingDataFileIO(0);

	//	�i�[
	int tmp;
	//	����
	int total = 3;

	//	�~���Ƀ\�[�g����
	for (int i = 0; i < total; i++) {
		for (int j = i + 1; j < total; j++) {
			if (m_rank[i] < m_rank[j]) {
				tmp = m_rank[i];
				m_rank[i] = m_rank[j];
				m_rank[j] = tmp;
			}
		}
	}

}

//========================================================//
//���e		�t�@�C���f�[�^�l�ƃX�R�A�̒l�̑召���ׂ�
//����		�Ȃ�
//�߂�l	�Ȃ�
//========================================================//
void RankFileIO::ArraySort(int score)
{
	//	�i�[
	int tmp;
	//	����
	int total = 4;

	int data[4] = { m_rank[0],m_rank[1],m_rank[2],score };

	//	�~���Ƀ\�[�g����
	for (int i = 0; i < total; i++) {
		for (int j = i + 1; j < total; j++) {
			if (data[i] < data[j]) {
				tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
			}
		}
	}

	//	�~���̃f�[�^�������L���O�f�[�^�ɓ����
	for (int k = 0; k < 3; k++)
	{
		m_rank[k] = data[k];
	}

}

