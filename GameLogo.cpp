//**********************************//
//*	名　前：GameLogo.cpp
//*	内　容：ロゴシーン
//*	日　付：2017.04.25
//* 更新日：2017.06.02
//*	制作者：N.Shibayama & Ayaka.Y
//**********************************//

#include "GameLogo.h"
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

GameLogo::GameLogo()
{
	//	初期化
	m_TimeCnt = 0;
	m_fadeCount = 0.0f;

	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/logo.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

	ComPtr<ID3D11Resource> blackResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/black_background.png",
			blackResource.GetAddressOf(),
			m_bkackTexture.ReleaseAndGetAddressOf()));

	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(resource.As(&clock));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(clockDesc.Width / 2.0f);
	m_origin.y = float(clockDesc.Height / 2.0f);

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

}

GameLogo::~GameLogo()
{

}

int GameLogo::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = LOGO;
	m_scene = LOGO;

	//	フェードイン
	if (m_TimeCnt <= 60)
	{
		m_fadeCount += 0.02f;
	}
	//	フェードアウト
	else if (m_TimeCnt > 120 && m_TimeCnt <= 180)
	{
		m_fadeCount -= 0.02f;
	}

	//	３秒経ったらタイトルシーンに移動
	if (m_TimeCnt > 180)
	{
		m_NextScene = TITLE;
	}
	return m_NextScene;

}

void GameLogo::RenderGame()
{

	//	スプライトの描画========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	//m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_bkackTexture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Vector4( m_fadeCount,m_fadeCount,m_fadeCount,m_fadeCount), 0.f, m_origin);

	m_spriteBatch->End();
	//==========================================================================================

}
