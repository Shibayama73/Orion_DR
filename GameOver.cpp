//**********************************//
//*	���@�O�FGameOver.cpp
//*	���@�e�F�I�[�o�[�V�[��
//*	���@�t�F2017.04.25
//* �X�V���F2017.06.02
//*	����ҁFN.Shibayama & Ayaka.Y
//**********************************//

#include "GameOver.h"
#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

#include "Game.h"
#include "pch.h"
#include <WICTextureLoader.h>

//	�T�E���h
#include "Resouces\Music\CueSheet_0.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

GameOver::GameOver()
{
	m_TimeCnt = 0;

	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 60.0f;
	m_grpH = 80.0f;

	if (FileIO(0, &m_score))
	{
		m_score = 0;
	}

	//	�����L���O�t�@�C���̐���
	m_rankFileIO = new RankFileIO();

	//	���ʃt�@�C���̓Ǎ���
	m_rankFileIO->SetRanking();
	m_rankFileIO->ArraySort(m_score);

	//	���ʃt�@�C���ɏ�����
	m_rankFileIO->RankingDataFileIO(1);

	//	�`��ǂݍ���============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_result.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/result.png",
			resource.GetAddressOf(),
			m_time_tex.ReleaseAndGetAddressOf()));


	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(resource.As(&clock));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = 0.0;
	m_origin.y = 0.0;

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

	//	�T�E���h�t�@�C���̓ǂݍ���
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

	//	�T�E���h�Đ�
	ADX2Le::Play(CRI_CUESHEET_0_RESULT);
}

GameOver::~GameOver()
{
	//	���ʃt�@�C���̍폜
	delete m_rankFileIO;
	//	�T�E���h���C�u�����̏I������
	ADX2Le::Finalize();
}

int GameOver::UpdateGame()
{
	m_NextScene = OVER;
	m_scene = OVER;

	//	�T�E���h�̍X�V
	ADX2Le::Update();

	//�G���^�[�L�[�Ń^�C�g���V�[��
	if (g_keyTracker->pressed.Enter)
	{
		m_NextScene = TITLE;
	}

	return m_NextScene;
}

void GameOver::RenderGame()
{
	//	�X�v���C�g�̕`��========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	m_spriteBatch->Draw(m_texture.Get(), Vector2(0,0), nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->End();
	//==========================================================================================

	DrawNum(200, 400, m_score);
	
	//	���ʃt�@�C���̕`��
	m_rankFileIO->Render(700.0f, 300.0f);

}

//��------------------------------------------------------------------��
//��*func�F���ԕ`��֐�
//��*arg�F�`��ʒu(float x�Afloat y)�A�`�悷�鐔�l(int n)
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void GameOver::DrawNum(float x, float y, int n)
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	int w = n;		//��Ɨp
	int i = 0;		//������

	RECT rect;

	if (w < 0)
	{
		rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };

		m_spriteBatch->Draw(m_time_tex.Get(), Vector2(x, y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

	}

	else
	{
		while (w)
		{
			m_grpX = (w % 10) * m_grpW;
			rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
			m_spriteBatch->Draw(m_time_tex.Get(), Vector2((x - i * m_grpW), y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

			w = w / 10;
			i++;
		}
	}

	m_spriteBatch->End();
}

//��------------------------------------------------------------------��
//��*func�F�t�@�C���ǂݏ����֐�
//��*arg�F�ǂݏ����w��i�O�F�ǂݍ��݁A�P�F�������݁j�A�ǂݏ����������ϐ�
//��*return�F����i�O�j�A�G���[�i�P�j
//��------------------------------------------------------------------��
int GameOver::FileIO(int io, int *score)
{
	char *Filename = "data.txt";
	FILE *fp;

	if (io == 0)
	{
		//�ǂݍ���
		fp = fopen(Filename, "r");
		if (fp == NULL)
		{
			return 1;
		}
		fscanf(fp, "%d", score);
	}
	else
	{
		//��������
		fp = fopen(Filename, "w");
		if (fp == NULL)
		{
			return 1;
		}
		fprintf(fp, "%d", score);
	}
	fclose(fp);
	return 0;
}

