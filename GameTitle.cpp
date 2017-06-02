//**********************************//
//*	名　前：GameTitle.cpp
//*	内　容：タイトルシーン
//*	日　付：2017.04.25
//* 更新日：2017.06.02
//*	制作者：N.Shibayama & Ayaka.Y
//**********************************//

#include "GameTitle.h"
#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

#include "Game.h"
#include "pch.h"
#include <WICTextureLoader.h>

//	サウンド
#include "Resouces\Music\CueSheet_0.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

GameTitle::GameTitle()
{
	m_TimeCnt = 0;

	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_title.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/title_font.png",
			resource.GetAddressOf(),
			m_texture2.ReleaseAndGetAddressOf()));
	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(resource.As(&clock));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = 0.0f;
	m_origin.y = 0.0f;

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

	//	サウンドファイルの読み込み
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

	//	サウンド再生
	ADX2Le::Play(CRI_CUESHEET_0_TITLE);

}

GameTitle::~GameTitle()
{
	//	サウンドライブラリの終了処理
	ADX2Le::Finalize();
}

int GameTitle::UpdateGame()
{
	//m_TimeCnt++;
	m_NextScene = TITLE;
	m_scene = TITLE;

	//	サウンドの更新
	ADX2Le::Update();

	//if (m_TimeCnt > 120)
	//{
	//	m_NextScene = PLAY;
	//}

	//エンターキーでプレイシーン
	if (g_keyTracker->pressed.Enter)
	{
		//	効果音
		ADX2Le::Play(CRI_CUESHEET_0_PUSH_KEY);

		m_NextScene = PLAY;
	}

	return m_NextScene;
}

void GameTitle::RenderGame()
{
	//	スプライトの描画========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	m_spriteBatch->Draw(m_texture.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_texture2.Get(), Vector2(220,520), nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->End();
	//==========================================================================================

}

