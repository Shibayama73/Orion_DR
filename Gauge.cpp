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
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//	瓶画像
	ComPtr<ID3D11Resource> bottleResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/bottle.png",
			bottleResource.GetAddressOf(),
			m_bottleTex.ReleaseAndGetAddressOf()));

	//	リソースから瓶のテクスチャと判断
	ComPtr<ID3D11Texture2D> bottle;
	DX::ThrowIfFailed(bottleResource.As(&bottle));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC bottleDesc;
	bottle->GetDesc(&bottleDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(bottleDesc.Width / 1.0f);
	m_origin.y = float(bottleDesc.Height / 2.0f);

	//	表示座標を画面中央に指定
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
	//	スプライトの描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	//	瓶
	m_spriteBatch->Draw(m_bottleTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	
	m_spriteBatch->End();
}
