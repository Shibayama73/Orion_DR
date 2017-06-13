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
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/black_background.png",
			backgroundResource.GetAddressOf(),
			m_bkackTexture.ReleaseAndGetAddressOf()));

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

}

GameRanking::~GameRanking()
{
	//	���ʃt�@�C���̍폜
	delete m_rankFileIO;
}

int GameRanking::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = RANKING;
	m_scene = RANKING;

	//	Enter�L�[�������ꂽ��^�C�g���V�[���Ɉړ�
	if (g_keyTracker->pressed.Enter)
	{
		m_NextScene = TITLE;
	}
	return m_NextScene;
}

void GameRanking::RenderGame()
{
	//	�X�v���C�g�̕`��========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	m_spriteBatch->Draw(m_bkackTexture.Get(), m_screenPos, nullptr, Colors::White, 0.0f, m_origin);
//	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Vector4(m_fadeCount, m_fadeCount, m_fadeCount, m_fadeCount), 0.f, m_origin);

	m_spriteBatch->End();
	//==========================================================================================

	//	���ʂ̕`��
	m_rankFileIO->Render(450.0f, 250.0f);

}

