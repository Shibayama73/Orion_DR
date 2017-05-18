//**********************************//
//*	���@�O�FClock.cpp
//*	���@�e�F���v�N���X
//*	���@�t�F2017.5.2
//*	����ҁFN.Shibayama
//**********************************//

#include "Clock.h"
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

//==================================//
//���e		�R���X�g���N�^
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
Clock::Clock()
{
	//������
	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 0.0f;
	m_grpH = 0.0f;
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_state = 0;


	//	�`��ǂݍ���============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//	���v�摜
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/clock.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

	//	�I���I���摜
	ComPtr<ID3D11Resource> resource2;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/longTip.png",
			resource2.GetAddressOf(),
			m_texture2.ReleaseAndGetAddressOf()));

	//	���\�[�X���玞�v�̃e�N�X�`���Ɣ��f
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

//==================================//
//���e		�f�X�g���N�^
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
Clock::~Clock()
{
}

//==================================//
//���e		�X�V
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
void Clock::Update()
{
}

//==================================//
//���e		�`��
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
void Clock::Render()
{
	//	�X�v���C�g�̕`��========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	
	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_texture2.Get(), m_screenPos+Vector2(120,0), nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();
	//==========================================================================================

}

//==================================//
//���e		�j�̏�Ԏ擾
//����		�Ȃ�
//�߂�l	���j(true)�Z�j(false)
//==================================//
bool Clock::getHand()
{
	return m_hand;
}

//==================================//
//���e		���j�̐�[���W�擾
//����		�Ȃ�
//�߂�l	��[���W(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getLongTipPos()
{
	return m_longTipPos;
}

//==================================//
//���e		�Z�j�̐�[���W�擾
//����		�Ȃ�
//�߂�l	��[���W(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getShotTipPos()
{
	return m_shotTipPos;
}

//==================================//
//���e		���v���ɐj����]������
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
void Clock::clockwise()
{
	
}

