//**********************************//
//*	GameLogo.cpp
//*	���S�V�[��
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GameLogo.h"
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

GameLogo::GameLogo()
{
	m_TimeCnt = 0;

	//	�`��ǂݍ���============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/logo.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(resource.As(&clock));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(clockDesc.Width / 2.0f);
	m_origin.y = float(clockDesc.Height / 2.0f);

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

}

GameLogo::~GameLogo()
{

}

int GameLogo::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = LOGO;
	m_scene = LOGO;

	if (m_TimeCnt > 120)
	{
		m_NextScene = TITLE;
	}
	return m_NextScene;

}

void GameLogo::RenderGame()
{
	//	�X�v���C�g�̕`��========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();
	//==========================================================================================

}
