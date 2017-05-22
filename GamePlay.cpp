//**********************************//
//*	GamePlay.cpp
//*	�v���C�V�[��
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GamePlay.h"
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

GamePlay::GamePlay()
{
	//m_TimeCnt = 0;

	//	���v����
	m_clock = new Clock();

	//�v���C���[�̐���
	m_player = new Player();



	////	�`��ǂݍ���============================================================================
	//m_deviceResources = Game::m_deviceResources.get();
	//m_spriteBatch = Game::m_spriteBatch.get();

	//ComPtr<ID3D11Resource> resource;
	//DX::ThrowIfFailed(
	//	CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/clock.png",
	//		resource.GetAddressOf(),
	//		m_texture.ReleaseAndGetAddressOf()));

	////	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	//ComPtr<ID3D11Texture2D> clock;
	//DX::ThrowIfFailed(resource.As(&clock));

	////	�e�N�X�`�����
	//CD3D11_TEXTURE2D_DESC clockDesc;
	//clock->GetDesc(&clockDesc);

	////	�e�N�X�`�����_���摜�̒��S�ɂ���
	//m_origin.x = float(clockDesc.Width / 2.0f);
	//m_origin.y = float(clockDesc.Height / 2.0f);

	////	�\�����W����ʒ����Ɏw��
	//m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	//m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	////==========================================================================================

}

GamePlay::~GamePlay()
{
	//	���v�j��
	delete m_clock;

	//�v���C���[�̔j��
	delete m_player;
}

int GamePlay::UpdateGame()
{
	m_NextScene = PLAY;
	m_scene = PLAY;

	//	�e�N���X�̍X�V
	//	���v�̍X�V
	m_clock->Update();
	m_player->Needle(m_clock->getLongTipPos(), m_clock->getLongTipOrigin());
	//	�v���C���[�̈ړ�����
	m_player->run(m_clock->getLongTipPos(), m_clock->getLongTipOrigin());

	//	�v���C���[�̍X�V
	m_player->Update();

	/*m_TimeCnt++;
	if (m_TimeCnt > 120)
	{
		m_NextScene = CLEAR;
	}*/


	return m_NextScene;
}

void GamePlay::RenderGame()
{
	//	���v�`��
	m_clock->Render();

	//�v���C���[�̕`��
	m_player->Render();


	////	�X�v���C�g�̕`��========================================================================
	//CommonStates m_states(m_deviceResources->GetD3DDevice());
	//m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	//m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);

	//m_spriteBatch->End();
	////==========================================================================================

}
