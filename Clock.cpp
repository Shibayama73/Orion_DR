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

const float ORIGINE_X = 400.0f;
const float ORIGINE_Y = 300.0f;
const float RADIUS = 310.0f;

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

	//	��[���W
	m_longTipPos = Vector2(0.0f, 0.0f);
	m_shortTipPos = Vector2(0.0f, 0.0f);

	//	��]
	m_rotLongPos = 0.0f;	//���j��]
	m_rotShortPos = 3.15f;	//�Z�j��]

	//	���W�p�x
	m_LTPos = 270.0f;		//���j���W�p�x
	m_STPos = 90.0f;		//�Z�j���W�p�x

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

	//	�Z�j�摜
	ComPtr<ID3D11Resource> shortTipRes;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/shortTip.png",
			shortTipRes.GetAddressOf(),
			m_ShortTipTex.ReleaseAndGetAddressOf()));

	//	���_�摜
	ComPtr<ID3D11Resource> OriginRes;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/origin.png",
			OriginRes.GetAddressOf(),
			m_OriginTex.ReleaseAndGetAddressOf()));

	//	���\�[�X���玞�v�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(clockRes.As(&clock));

	////	���\�[�X���璷�j�̃e�N�X�`���Ɣ��f
	//ComPtr<ID3D11Texture2D> longTip;
	//DX::ThrowIfFailed(clockRes.As(&longTip));

	////	���\�[�X���猴�_�̃e�N�X�`���Ɣ��f
	//ComPtr<ID3D11Texture2D> originTip;
	//DX::ThrowIfFailed(clockRes.As(&originTip));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	////	�e�N�X�`�����
	//CD3D11_TEXTURE2D_DESC longTipDesc;
	//longTip->GetDesc(&longTipDesc);

	////	�e�N�X�`�����
	//CD3D11_TEXTURE2D_DESC originDesc;
	//originTip->GetDesc(&originDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(clockDesc.Width / 2.0f);
	m_origin.y = float(clockDesc.Height / 2.0f);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	//m_longTOri.x = float(longTipDesc.Width / 2.0f);
	//m_longTOri.y = float(longTipDesc.Height / 1.2f);
	//m_longTOri.x = float(longTipDesc.Width / 2.0f);
	//m_longTOri.y = float(longTipDesc.Height / 1.0f);

	////	�e�N�X�`�����_���摜�̒��S�ɂ���
	//m_ori.x = float(originDesc.Width / 2.0f);
	//m_ori.y = float(originDesc.Height / 2.0f);

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
//	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f - 40.0f;

	//	�\�����W����ʒ����Ɏw��
	//m_longTPos.x = m_deviceResources->GetOutputSize().right / 1.16f;
	//m_longTPos.y = m_deviceResources->GetOutputSize().bottom / 3.8f;
//	m_longTPos.x = m_deviceResources->GetOutputSize().right / 2.0f;	//2.03
//	m_longTPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;	//2.05

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
	//	���v����]
	this->clockwise();
}

//==================================//
//���e		�`��
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
void Clock::Render()
{
	//	�X�v���C�g�̕`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	//	���v
	m_spriteBatch->Draw(m_clockTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	//	���j
	m_spriteBatch->Draw(m_LongTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotLongPos);
	//	�Z�j
	m_spriteBatch->Draw(m_ShortTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotShortPos);
	//	���_
	m_spriteBatch->Draw(m_OriginTex.Get(), m_screenPos+Vector2(-30.0f,-35.0f), nullptr, Colors::White, 0.f);
	m_spriteBatch->End();
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
//���e		�j�̌��_���擾����
//����		�Ȃ�
//�߂�l	�j�̌��_(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getLongTipOrigin()
{
	return m_screenPos;
}

//==================================//
//���e		���j�̐�[���W�擾
//����		�Ȃ�
//�߂�l	��[���W(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getLongTipPos()
{
	//	���j�p�x
	float m_longTipAng;

	//	��]�p�x�̎擾
	m_longTipAng = XMConvertToRadians(m_LTPos);
	//	�O�p�֐�
	m_longTipPos = Vector2(ORIGINE_X + (RADIUS * cosf(m_longTipAng)), ORIGINE_Y + (RADIUS * sinf(m_longTipAng)));

	return m_longTipPos;
}

//==================================//
//���e		�Z�j�̐�[���W�擾
//����		�Ȃ�
//�߂�l	��[���W(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getShortTipPos()
{
	//	�Z�j�p�x
	float m_shortTipAng;

	//	��]�p�x�̎擾
	m_shortTipAng = XMConvertToRadians(m_STPos);

	m_shortTipPos = Vector2(ORIGINE_X + (RADIUS * cosf(m_shortTipAng)), ORIGINE_Y + (RADIUS * sinf(m_shortTipAng)));

	return m_shortTipPos;
}

//==================================//
//���e		���v���ɐj����]������
//����		�Ȃ�
//�߂�l	�Ȃ�
//==================================//
void Clock::clockwise()
{
	//	��]������
	m_rotLongPos += 0.05f;
	m_rotShortPos += 0.005f;

	//	��[���W�p�x��360�x�ȓ��̂Ƃ�
	if (m_LTPos <= 360.0f) {
		//	��[���W�̊p�x�����炷
		m_LTPos += 0.01f;
	}
	else {
		m_LTPos = 0.0f;
	}

	//	��[���W�p�x��360�x�ȓ��̂Ƃ�
	if (m_STPos <= 360.0f) {
		//	��[���W�̊p�x�����炷
		m_STPos += 0.01f;
	}
	else {
		m_STPos = 0.0f;
	}

}

//=============================================================//
//���e		���j�ƒZ�j�̊Ԃ̊p�x�Z�o(3�_����Ȃ��p�����߂�)
//����		���j��[���W(Vec2)�A�Z�j��[���W(Vec2)
//�߂�l	�Ȃ��p(float)
//=============================================================//
float Clock::calAngle()
{
	//	���j�̒���
	Vector2 longLeng = m_longTipPos - Vector2(ORIGINE_X, ORIGINE_Y);
	//	�Z�j�̒���
	Vector2 shortLeng = m_shortTipPos - Vector2(ORIGINE_X, ORIGINE_Y);

	//	���q
	float numer = longLeng.x * shortLeng.x + longLeng.y * shortLeng.y;
	//	����
	float denom = sqrtf(longLeng.x * longLeng.x + longLeng.y * longLeng.y)*
		sqrtf(shortLeng.x * shortLeng.x + shortLeng.y * shortLeng.y);

	//	cos�Ƃ����߂�
	float cosTheta = numer / denom;
	//	�Ȃ��p(��)�ɕϊ�
	float angle = acosf(cosTheta);

	return angle;
}

