//**********************************//
//*	���@�O�FGameTitle.cpp
//*	���@�e�F�^�C�g���V�[��
//*	���@�t�F2017.04.25
//* �X�V���F2017.06.02
//*	����ҁFN.Shibayama & Ayaka.Y
//**********************************//

#include "GameTitle.h"
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

GameTitle::GameTitle()
{
	m_TimeCnt = 0;
	m_sceneFlag = SCENE_FLAG::PLAY_FLAG;

	//	�`��ǂݍ���============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_title.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/serect_title.png",
			resource.GetAddressOf(),
			m_serectTexture.ReleaseAndGetAddressOf()));
	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(resource.As(&clock));
	ComPtr<ID3D11Texture2D> serect;
	DX::ThrowIfFailed(resource.As(&serect));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);
	CD3D11_TEXTURE2D_DESC serectDesc;
	serect->GetDesc(&serectDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = 0.0f;
	m_origin.y = 0.0f;

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

	//	�T�E���h�t�@�C���̓ǂݍ���
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

	//	�T�E���h�Đ�
	ADX2Le::Play(CRI_CUESHEET_0_TITLE);

}

GameTitle::~GameTitle()
{
	//	�T�E���h���C�u�����̏I������
	ADX2Le::Finalize();
}

int GameTitle::UpdateGame()
{
	//m_TimeCnt++;
	m_NextScene = TITLE;
	m_scene = TITLE;

	//	�T�E���h�̍X�V
	ADX2Le::Update();

	//	�E�L�[�������ꂽ�Ƃ�
	if (g_keyTracker->pressed.Right)
	{
		//	�I�𕔕��̈ړ�
		m_sceneFlag++;

		//	�V�[���t���O�������Ƃ�
		if (m_sceneFlag >= 4) {
			//	�v���C�I���ɖ߂�
			m_sceneFlag = SCENE_FLAG::PLAY_FLAG;
		}
	}
	//	���L�[�������ꂽ�Ƃ�
	else if (g_keyTracker->pressed.Left)
	{
		//	�I�𕔕��̈ړ�
		m_sceneFlag--;

		//	�V�[���t���O�������Ƃ�
		if (m_sceneFlag < 0) {
			//	�G���h�I���ɖ߂�
			m_sceneFlag = SCENE_FLAG::END_FLAG;
		}
	}

	//	Enter�L�[�������ꂽ�Ƃ�
	else if (g_keyTracker->pressed.Enter)
	{
		//	���ʉ�
		ADX2Le::Play(CRI_CUESHEET_0_PUSH_KEY);

		//	�V�[���t���O
		switch (m_sceneFlag)
		{
		case SCENE_FLAG::PLAY_FLAG:
			//	�v���C�V�[���Ɉړ�
			m_NextScene = PLAY;
			break;
		case SCENE_FLAG::STORY_FLAG:
			//	����V�[���Ɉړ�
			m_NextScene = STORY;
			break;
		case SCENE_FLAG::RANK_FLAG:
			//	�����L���O�V�[���Ɉړ�
			m_NextScene = RANKING;
			break;
		case SCENE_FLAG::END_FLAG:
			//	�Q�[�����I������
			PostQuitMessage(0);
			break;
		}
	}

	return m_NextScene;
}

void GameTitle::RenderGame()
{
	//	�X�v���C�g�̕`��========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	m_spriteBatch->Draw(m_texture.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
	
	//	�I�𕔕�
	switch (m_sceneFlag)
	{
	case SCENE_FLAG::PLAY_FLAG:
		m_spriteBatch->Draw(m_serectTexture.Get(), Vector2(45, 305), nullptr, Colors::White, 0.f, m_origin);
		break;
	case SCENE_FLAG::STORY_FLAG:
		m_spriteBatch->Draw(m_serectTexture.Get(), Vector2(222, 435), nullptr, Colors::White, 0.f, m_origin);
		break;
	case SCENE_FLAG::RANK_FLAG:
		m_spriteBatch->Draw(m_serectTexture.Get(), Vector2(461, 435), nullptr, Colors::White, 0.f, m_origin);
		break;
	case SCENE_FLAG::END_FLAG:
		m_spriteBatch->Draw(m_serectTexture.Get(), Vector2(642, 305), nullptr, Colors::White, 0.f, m_origin);
		break;
	}

	m_spriteBatch->End();
	//==========================================================================================

}

