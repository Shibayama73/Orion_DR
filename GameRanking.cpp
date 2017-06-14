//**********************************//
//*	���@�O�FGameRanking.cpp
//*	���@�e�F�����L���O�V�[��
//*	���@�t�F2017.06.12
//* �X�V���F2017.06.12
//*	����ҁFN.Shibayama
//**********************************//

#include "GameRanking.h"

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

GameRanking::GameRanking()
{
	//	������
	m_TimeCnt = 0;

	//	���ʃt�@�C���̏�����
	m_rankFileIO = new RankFileIO();
	//	���ʃt�@�C���̓Ǎ���
	m_rankFileIO->SetRanking();

	//	�`��ǂݍ���============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> backgroundResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_rank.png",
			backgroundResource.GetAddressOf(),
			m_backTexture.ReleaseAndGetAddressOf()));

	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> background;
	DX::ThrowIfFailed(backgroundResource.As(&background));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC backgroundDesc;
	background->GetDesc(&backgroundDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(backgroundDesc.Width / 2.0f);
	m_origin.y = float(backgroundDesc.Height / 2.0f);

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

	//	�T�E���h�t�@�C���̓ǂݍ���
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

}

GameRanking::~GameRanking()
{
	//	���ʃt�@�C���̍폜
	delete m_rankFileIO;
	//	�T�E���h���C�u�����̏I������
	ADX2Le::Finalize();
}

int GameRanking::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = RANKING;
	m_scene = RANKING;

	//	�T�E���h�̍X�V
	ADX2Le::Update();

	//	Enter�L�[�������ꂽ��
	if (g_keyTracker->pressed.Enter)
	{
		//	���ʉ�
		ADX2Le::Play(CRI_CUESHEET_0_PUSH_KEY);
		//	�^�C�g���V�[���Ɉړ�
		m_NextScene = TITLE;
	}
	return m_NextScene;
}

void GameRanking::RenderGame()
{
	//	�w�i�X�v���C�g�̕`��====================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	m_spriteBatch->Draw(m_backTexture.Get(), m_screenPos, nullptr, Colors::White, 0.0f, m_origin);
	m_spriteBatch->End();
	//==========================================================================================

	//	���ʂ̕`��
	m_rankFileIO->Render(450.0f, 250.0f, 150.0f);

}

