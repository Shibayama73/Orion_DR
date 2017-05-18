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

	m_rotPos = 0.0f;	//��]

	//	�`��ǂݍ���============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//	���v�摜
	ComPtr<ID3D11Resource> clockRes;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/clock.png",
			clockRes.GetAddressOf(),
			m_clockTex.ReleaseAndGetAddressOf()));

	//	���j�摜
	ComPtr<ID3D11Resource> LongTipRes;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/longTip.png",
			LongTipRes.GetAddressOf(),
			m_LongTipTex.ReleaseAndGetAddressOf()));

	//	���\�[�X���玞�v�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(clockRes.As(&clock));

	//	���\�[�X���璷�j�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> longTip;
	DX::ThrowIfFailed(clockRes.As(&longTip));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC longTipDesc;
	clock->GetDesc(&longTipDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(clockDesc.Width / 2.0f);
	m_origin.y = float(clockDesc.Height / 2.0f);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_longTOri.x = float(longTipDesc.Width / 2.0f);
	m_longTOri.y = float(longTipDesc.Height / 1.2f);

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//	�\�����W����ʒ����Ɏw��
	m_longTPos.x = m_deviceResources->GetOutputSize().right / 1.16f;
	m_longTPos.y = m_deviceResources->GetOutputSize().bottom / 3.8f;

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
	clockwise();

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
	
	//	���v
	m_spriteBatch->Draw(m_clockTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	//	���j
	//m_spriteBatch->Draw(m_LongTipTex.Get(), m_longTPos, nullptr, Colors::White, m_headPos, m_longTOri);
	m_spriteBatch->Draw(m_LongTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotPos);

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
	//	��]������
	m_rotPos += 0.01f;

}

