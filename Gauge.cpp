//**********************************//
//*	���@�O�FGauge.cpp
//*	���@�e�F���Ќv�ʃQ�[�W�N���X
//*	���@�t�F2017.5.24
//*	����ҁFN.Shibayama
//**********************************//

#include "Gauge.h"
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

Gauge::Gauge()
{
	//	������
	m_gradation = 0;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpX = 115.0f;
	m_grpY = 571.0f;
	m_grpW = -115.0f;	//115
	m_grpH = -50.0f;	//571
	m_posX = 0.0f;
	m_posY = 0.0f;

	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//	�����v�摜
	ComPtr<ID3D11Resource> hourglassResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/gauge1.png",
			hourglassResource.GetAddressOf(),
			m_hourglassTex.ReleaseAndGetAddressOf()));

	//	�Q�[�W�F�摜
	ComPtr<ID3D11Resource> colorResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/gauge2.png",
			colorResource.GetAddressOf(),
			m_colorTex.ReleaseAndGetAddressOf()));

	//	���\�[�X����e�N�X�`���Ɣ��f
	//	�����v
	ComPtr<ID3D11Texture2D> hourglass;
	DX::ThrowIfFailed(hourglassResource.As(&hourglass));
	//	�Q�[�W�F
	ComPtr<ID3D11Texture2D> gradation;
	DX::ThrowIfFailed(colorResource.As(&gradation));

	//	�e�N�X�`�����
	//	�����v
	CD3D11_TEXTURE2D_DESC hourglassDesc;
	hourglass->GetDesc(&hourglassDesc);
	//	�Q�[�W�F
	CD3D11_TEXTURE2D_DESC gradationDesc;
	gradation->GetDesc(&gradationDesc);

	//	�e�N�X�`�����_(�E��)�̎w��
	//	�����v
	m_origin.x = float(hourglassDesc.Width / 1.0f);
	m_origin.y = float(hourglassDesc.Height / 1.0f);
	//	�Q�[�W�F
	m_gradationOrigin.x = float(gradationDesc.Width / 1.0f);
	m_gradationOrigin.y = float(gradationDesc.Height / 1.0f);

	//	�\�����W�̎w��
	//	�����v
	m_screenPos.x = m_deviceResources->GetOutputSize().right - 10.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom - 50.0f;
	//	�Q�[�W�F
	/*m_gradationPos.x = m_deviceResources->GetOutputSize().right - 10.0f;
	m_gradationPos.y = m_deviceResources->GetOutputSize().bottom - 50.0f;*/
	m_gradationPos.x = m_deviceResources->GetOutputSize().right + m_grpX - 10.0f;
	m_gradationPos.y = m_deviceResources->GetOutputSize().bottom + m_grpY - 50.0f;
	
}

Gauge::~Gauge()
{
}

void Gauge::Update()
{
}

void Gauge::Render()
{
	//	�X�v���C�g�̕`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());
	//	�����v
	m_spriteBatch->Draw(m_hourglassTex.Get(), m_screenPos, nullptr, Colors::White, 0.0f, m_origin);
	//	�Q�[�W�F
	RECT rect;
	//if (m_gradation)
	{
	//	m_gradation = (m_gradation % 14) * m_grpW;
		//rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
		rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
		//	�Q�[�W�F�̕`��
		m_spriteBatch->Draw(m_colorTex.Get(), m_gradationPos, &rect, Colors::White, 0.0f, m_gradationOrigin);

	//	m_gradation = m_gradation / 14;
	}

	m_spriteBatch->End();
}

//	�O��Ƃ��Ă��̊֐��͒͂܂ꂽ��Ԃ����������Ԃ̂Ƃ��Ɏg�p�������̂Ƃ���
void Gauge::addGradation(int state)
{
	//	state����������Ԃ̂Ƃ�
	if (state == FRAGMENT_LOSS)
	{
		//	�l�����Z����
		m_gradation++;
	}

}

int Gauge::getGradation()
{
	return m_gradation;
}
