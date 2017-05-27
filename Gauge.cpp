//**********************************//
//*	名　前：Gauge.cpp
//*	内　容：欠片計量ゲージクラス
//*	日　付：2017.5.24
//*	制作者：N.Shibayama
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
	//	初期化
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

	//	瓶画像
	ComPtr<ID3D11Resource> bottleResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/bottle1.png",
			bottleResource.GetAddressOf(),
			m_bottleTex.ReleaseAndGetAddressOf()));

	//	欠片色画像
	ComPtr<ID3D11Resource> colorResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/bottle2.png",
			colorResource.GetAddressOf(),
			m_colorTex.ReleaseAndGetAddressOf()));

	//	リソースからテクスチャと判断
	//	瓶
	ComPtr<ID3D11Texture2D> bottle;
	DX::ThrowIfFailed(bottleResource.As(&bottle));
	//	欠片色
	ComPtr<ID3D11Texture2D> gradation;
	DX::ThrowIfFailed(bottleResource.As(&gradation));

	//	テクスチャ情報
	//	瓶
	CD3D11_TEXTURE2D_DESC bottleDesc;
	bottle->GetDesc(&bottleDesc);
	//	欠片色
	CD3D11_TEXTURE2D_DESC gradationDesc;
	gradation->GetDesc(&gradationDesc);

	//	テクスチャ原点を画像の中心にする
	//	瓶
	m_origin.x = float(bottleDesc.Width / 1.0f);
	m_origin.y = float(bottleDesc.Height / 2.0f);
	//	欠片色
	m_gradationOrigin.x = float(gradationDesc.Width / 1.0f);
	m_gradationOrigin.y = float(gradationDesc.Height / 1.0f);

	//	表示座標を画面中央に指定
	//	瓶
	m_screenPos.x = m_deviceResources->GetOutputSize().right - 10.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;
	//	欠片色
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
	//	スプライトの描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());
	//	瓶
	m_spriteBatch->Draw(m_bottleTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	//	欠片色
	RECT rect;
	if (m_gradation)
	{
	//	m_gradation = (m_gradation % 14) * m_grpW;
		//rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
		rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH)*(m_gradation % 14) };
		//	欠片色の描画
		m_spriteBatch->Draw(m_colorTex.Get(), m_gradationPos, &rect, Colors::White, 0.0f, m_gradationOrigin);

	//	m_gradation = m_gradation / 14;
	}

	m_spriteBatch->End();
}

//	前提としてこの関数は掴まれた状態から消えた状態のときに使用されるものとする
void Gauge::addGradation(int state)
{
	//	stateが消えた状態のとき
	if (state == FRAGMENT_LOSS)
	{
		//	値を加算する
		m_gradation++;
	}

}

int Gauge::getGradation()
{
	return m_gradation;
}
