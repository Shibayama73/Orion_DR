//��----------------------------------------------------��
//��*�t�@�C�����FGameStory.cpp							��
//��*���e�@�@�@�F�X�g�[���[����V�[��					��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.06.15								��
//��----------------------------------------------------��
#include "pch.h"
#include "GameStory.h"
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


GameStory::GameStory()
{
	//	�`��ǂݍ���============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/howto1.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/howto2.png",
			resource.GetAddressOf(),
			m_texture2.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/howto3.png",
			resource.GetAddressOf(),
			m_texture3.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/howto4.png",
			resource.GetAddressOf(),
			m_texture4.ReleaseAndGetAddressOf()));

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
	ADX2Le::Play(CRI_CUESHEET_0_STORY);
	
	m_page = 0;
}


GameStory::~GameStory()
{
	//	�T�E���h���C�u�����̏I������
	ADX2Le::Finalize();
}

int GameStory::UpdateGame()
{
	m_NextScene = STORY;
	m_scene = STORY;

	//	�T�E���h�̍X�V
	ADX2Le::Update();

	if (g_keyTracker->pressed.Enter)
	{
		//	���ʉ�
		ADX2Le::Play(CRI_CUESHEET_0_PAGE);

		m_page++;
		if (m_page > 3)
		{
			m_NextScene = TITLE;
		}
	}

	return m_NextScene;
}

void GameStory::RenderGame()
{
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	switch (m_page)
	{
	case 0:
		m_spriteBatch->Draw(m_texture.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
		break;
	case 1:
		m_spriteBatch->Draw(m_texture2.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
		break;
	case 2:
		m_spriteBatch->Draw(m_texture3.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
		break;
	case 3:
		m_spriteBatch->Draw(m_texture4.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
		break;
	}

	m_spriteBatch->End();

}
