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
	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 75.0f;
	m_grpH = 52.0f;
	m_posX = 0.0f;
	m_posY = 0.0f;

	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//	�r�摜
	ComPtr<ID3D11Resource> bottleResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/bottle1.png",
			bottleResource.GetAddressOf(),
			m_bottleTex.ReleaseAndGetAddressOf()));

	//	���АF�摜
	ComPtr<ID3D11Resource> colorResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/bottle2.png",
			colorResource.GetAddressOf(),
			m_colorTex.ReleaseAndGetAddressOf()));

	//	���\�[�X����e�N�X�`���Ɣ��f
	//	�r
	ComPtr<ID3D11Texture2D> bottle;
	DX::ThrowIfFailed(bottleResource.As(&bottle));
	//	���АF
	ComPtr<ID3D11Texture2D> gradation;
	DX::ThrowIfFailed(bottleResource.As(&gradation));

	//	�e�N�X�`�����
	//	�r
	CD3D11_TEXTURE2D_DESC bottleDesc;
	bottle->GetDesc(&bottleDesc);
	//	���АF
	CD3D11_TEXTURE2D_DESC gradationDesc;
	gradation->GetDesc(&gradationDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	//	�r
	m_origin.x = float(bottleDesc.Width / 1.0f);
	m_origin.y = float(bottleDesc.Height / 2.0f);
	//	���АF
	m_gradationOrigin.x = float(gradationDesc.Width / 1.0f);
	m_gradationOrigin.y = float(gradationDesc.Height / 1.0f);

	//	�\�����W����ʒ����Ɏw��
	//	�r
	m_screenPos.x = m_deviceResources->GetOutputSize().right - 10.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;
	//	���АF
	m_gradationPos.x = m_deviceResources->GetOutputSize().right - 10.0f;
	m_gradationPos.y = m_deviceResources->GetOutputSize().bottom / 1.0f;

	
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
	//	�r
	m_spriteBatch->Draw(m_bottleTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	//	���АF
	RECT rect;
	if (m_gradation)
	{
	//	m_gradation = (m_gradation % 14) * m_grpW;
		//rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
		rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH)*(m_gradation % 14) };
		//	���АF�̕`��
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
