//**********************************//
//*	GameOver.cpp
//*	オーバーシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GameOver.h"
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

GameOver::GameOver()
{
	m_TimeCnt = 0;

	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_result.jpg",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

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

	//	サウンドファイルの読み込み
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

	//	サウンド再生
	ADX2Le::Play(CRI_CUESHEET_0_RESULT);
}

GameOver::~GameOver()
{
	//	サウンドライブラリの終了処理
	ADX2Le::Finalize();
}

int GameOver::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = OVER;
	m_scene = OVER;

	//	サウンドの更新
	ADX2Le::Update();

	//if (m_TimeCnt > 120)
	//{
	//	m_NextScene = TITLE;
	//}


	//スペースキーでタイトルシーン
	if (g_keyTracker->pressed.Space)
	{
		m_NextScene = TITLE;
	}


	return m_NextScene;
}

void GameOver::RenderGame()
{
	//	スプライトの描画========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();
	//==========================================================================================

}
