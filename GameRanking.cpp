//**********************************//
//*	名　前：GameRanking.cpp
//*	内　容：ランキングシーン
//*	日　付：2017.06.12
//* 更新日：2017.06.12
//*	制作者：N.Shibayama
//**********************************//

#include "GameRanking.h"

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

GameRanking::GameRanking()
{
	//	初期化
	m_TimeCnt = 0;

	//	順位ファイルの初期化
	m_rankFileIO = new RankFileIO();
	//	順位ファイルの読込み
	m_rankFileIO->SetRanking();

	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> backgroundResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_rank.png",
			backgroundResource.GetAddressOf(),
			m_backTexture.ReleaseAndGetAddressOf()));

	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> background;
	DX::ThrowIfFailed(backgroundResource.As(&background));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC backgroundDesc;
	background->GetDesc(&backgroundDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(backgroundDesc.Width / 2.0f);
	m_origin.y = float(backgroundDesc.Height / 2.0f);

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================

	//	サウンドファイルの読み込み
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

}

GameRanking::~GameRanking()
{
	//	順位ファイルの削除
	delete m_rankFileIO;
	//	サウンドライブラリの終了処理
	ADX2Le::Finalize();
}

int GameRanking::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = RANKING;
	m_scene = RANKING;

	//	サウンドの更新
	ADX2Le::Update();

	//	Enterキーが押されたら
	if (g_keyTracker->pressed.Enter)
	{
		//	効果音
		ADX2Le::Play(CRI_CUESHEET_0_PUSH_KEY);
		//	タイトルシーンに移動
		m_NextScene = TITLE;
	}
	return m_NextScene;
}

void GameRanking::RenderGame()
{
	//	背景スプライトの描画====================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	m_spriteBatch->Draw(m_backTexture.Get(), m_screenPos, nullptr, Colors::White, 0.0f, m_origin);
	m_spriteBatch->End();
	//==========================================================================================

	//	順位の描画
	m_rankFileIO->Render(450.0f, 250.0f, 150.0f);

}

