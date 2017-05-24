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
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//	�r�摜
	ComPtr<ID3D11Resource> bottleResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/bottle.png",
			bottleResource.GetAddressOf(),
			m_bottleTex.ReleaseAndGetAddressOf()));

	//	���\�[�X����r�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> bottle;
	DX::ThrowIfFailed(bottleResource.As(&bottle));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC bottleDesc;
	bottle->GetDesc(&bottleDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(bottleDesc.Width / 1.0f);
	m_origin.y = float(bottleDesc.Height / 2.0f);

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right - 10.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f + 20.0f;

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
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	//	�r
	m_spriteBatch->Draw(m_bottleTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	
	m_spriteBatch->End();
}
