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

//�f�o�b�N�p
#include <Windows.h>
#include <Windef.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

const float ORIGINE_X = 450.0f;
const float ORIGINE_Y = 310.0f;
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
	m_rotLongPos = 3.15f;	//���j��]
	m_rotShortPos = 3.15f;	//�Z�j��]

	//	���W�p�x
//	m_LTPos = 0.0f;		//���j���W�p�x
//	m_STPos = 0.0f;		//�Z�j���W�p�x

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
	//	���v
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(clockRes.As(&clock));
	//	���j
	ComPtr<ID3D11Texture2D> longTip;
	DX::ThrowIfFailed(LongTipRes.As(&longTip));
	//	�Z�j
	ComPtr<ID3D11Texture2D> shortTip;
	DX::ThrowIfFailed(shortTipRes.As(&shortTip));
	//	���_
	ComPtr<ID3D11Texture2D> originTip;
	DX::ThrowIfFailed(OriginRes.As(&originTip));

	//	�e�N�X�`�����
	//	���v
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);
	//	���j
	CD3D11_TEXTURE2D_DESC longTipDesc;
	longTip->GetDesc(&longTipDesc);
	//	�Z�j
	CD3D11_TEXTURE2D_DESC shortTipDesc;
	shortTip->GetDesc(&shortTipDesc);
	//	���_
	CD3D11_TEXTURE2D_DESC originDesc;
	originTip->GetDesc(&originDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	//	���v
	m_origin.x = float(clockDesc.Width / 2.0f);
	m_origin.y = float(clockDesc.Height / 2.0f);
	//	���j
	m_longTOri.x = float(longTipDesc.Width / 2.0f);
	m_longTOri.y = float(longTipDesc.Height / 1.0f);
	//	�Z�j
	m_shortTOri.x = float(shortTipDesc.Width / 2.0f);
	m_shortTOri.y = float(shortTipDesc.Height / 1.0f);
	//	���_
	m_ori.x = float(originDesc.Width / 2.0f);
	m_ori.y = float(originDesc.Height / 2.0f);

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f - 40.0f;

	//==========================================================================================
	//�ʏ펞�摜
	ComPtr<ID3D11Resource> time_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/number.png",
			time_resource.GetAddressOf(),
			m_time_tex.ReleaseAndGetAddressOf()));

	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> time;
	DX::ThrowIfFailed(time_resource.As(&time));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC timeDesc;
	time->GetDesc(&timeDesc);

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
	m_spriteBatch->Draw(m_LongTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotLongPos, m_longTOri);
	//	�Z�j
	m_spriteBatch->Draw(m_ShortTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotShortPos, m_shortTOri);
	//	���_
	m_spriteBatch->Draw(m_OriginTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_ori);
	m_spriteBatch->End();

	//�f�o�b�N�p���l�`��
	//DrawNum(100, 80, (int)m_longTipPos.x);
	//DrawNum(100, 100, (int)m_longTipPos.y);

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
DirectX::SimpleMath::Vector2 Clock::getOrigin()
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
	Vector2 position;

	position.x = (sinf(-m_rotLongPos) * 310.0f) + 450.0f;
	position.y = (cosf(-m_rotLongPos) * 310.0f) + 310.0f;

	return position;

	////	���j�p�x
	//float m_longTipAng;
	////	��]�p�x�̎擾
	//m_longTipAng = XMConvertToRadians(m_LTPos);
	////	�O�p�֐�
	//m_longTipPos = Vector2(ORIGINE_X + (RADIUS * cosf(m_longTipAng)), ORIGINE_Y + (RADIUS * sinf(m_longTipAng)));
	//return m_longTipPos;
}

//==================================//
//���e		�Z�j�̐�[���W�擾
//����		�Ȃ�
//�߂�l	��[���W(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getShortTipPos()
{
	Vector2 position;

	position.x = (sinf(-m_rotShortPos) * 198.0f) + 450.0f;
	position.y = (cosf(-m_rotShortPos) * 198.0f) + 310.0f;

	return position;

	////	�Z�j�p�x
	//float m_shortTipAng;
	////	��]�p�x�̎擾
	//m_shortTipAng = XMConvertToRadians(m_STPos);
	//m_shortTipPos = Vector2(ORIGINE_X + (RADIUS * cosf(m_shortTipAng)), ORIGINE_Y + (RADIUS * sinf(m_shortTipAng)));
	//return m_shortTipPos;
}

//==================================//
//���e		���j�̉�]�p�x�擾
//����		�Ȃ�
//�߂�l	�p�x(float)
//==================================//
float Clock::getRotLong()
{
	return m_rotLongPos;
}

//==================================//
//���e		�Z�j�̉�]�p�x�擾
//����		�Ȃ�
//�߂�l	�p�x(float)
//==================================//
float Clock::getRotShort()
{
	return m_rotShortPos;
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

	////	��[���W�p�x��360�x�ȓ��̂Ƃ�
	//if (m_LTPos <= 360.0f) {
	//	//	��[���W�̊p�x�����炷
	//	m_LTPos += 0.01f;
	//}
	//else {
	//	m_LTPos = 0.0f;
	//}

	////	��[���W�p�x��360�x�ȓ��̂Ƃ�
	//if (m_STPos <= 360.0f) {
	//	//	��[���W�̊p�x�����炷
	//	m_STPos += 0.01f;
	//}
	//else {
	//	m_STPos = 0.0f;
	//}

}


////=============================================================//
////���e		3�_�̍��W����Ȃ��p�̎Z�o
////����		���_(Vec2)�A���j��[���W(Vec2)�A�Z�j��[���W(Vec2)
////�߂�l	�Ȃ��p(float)
////=============================================================//
//float Clock::calAngle(Vector2 origin, Vector2 longTip, Vector2 shortTip)
//{
//	//	���_����longTip�܂ł̒���
//	Vector2 longLeng = longTip - origin;
//	//	���_����shortTip�܂ł̒���
//	Vector2 shortLeng = shortTip - origin;
//
//	//	���q
//	float numer = longTip.x * shortTip.x + longTip.y * shortTip.y;
//	//	����
//	float denom = sqrtf(longTip.x * longTip.x + longTip.y * longTip.y)*
//		sqrtf(shortTip.x * shortTip.x + shortTip.y * shortTip.y);
//
//	//	cos�Ƃ����߂�
//	float cosTheta = numer / denom;
//	//	�Ȃ��p(��)�ɕϊ�
//	float angle = acosf(cosTheta);
//
//	return angle;
//}

//��------------------------------------------------------------------��
//��*func�F���ԕ`��֐�
//��*arg�F�`��ʒu(float x�Afloat y)�A�`�悷�鐔�l(int n)
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Clock::DrawNum(float x, float y, int n)
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	int w = n;		//��Ɨp
	int i = 0;		//������

	RECT rect;

	if (w == 0)
	{
		rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };

		m_spriteBatch->Draw(m_time_tex.Get(), Vector2(x, y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

		//DrawRectGraph(x, y, 0, 48, 25, 32, g_PongImage, TRUE, FALSE);
	}

	else
	{
		while (w)
		{
			m_grpX = (w % 10) * 25;
			rect = { (LONG)0, (LONG)48, (LONG)(m_grpX + 25), (LONG)(48 + 32) };
			m_spriteBatch->Draw(m_time_tex.Get(), Vector2((x - i * 25), y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

			//DrawRectGraph(x - i * 25, y, (w % 10) * 25, 48, 25, 32, g_PongImage, TRUE, FALSE);
			w = w / 10;
			i++;
		}
	}

	m_spriteBatch->End();
}


