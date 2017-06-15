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
	m_sceneFlag = SCENE_FLAG::PLAY_FLAG;

	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_title.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/serect_title.png",
			resource.GetAddressOf(),
			m_serectTexture.ReleaseAndGetAddressOf()));
	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(resource.As(&clock));
	ComPtr<ID3D11Texture2D> serect;
	DX::ThrowIfFailed(resource.As(&serect));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);
	CD3D11_TEXTURE2D_DESC serectDesc;
	serect->GetDesc(&serectDesc);

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

	//	右キーが押されたとき
	if (g_keyTracker->pressed.Right)
	{
		//	選択部分の移動
		m_sceneFlag++;

		//	シーンフラグが無いとき
		if (m_sceneFlag >= 4) {
			//	プレイ選択に戻る
			m_sceneFlag = SCENE_FLAG::PLAY_FLAG;
		}
	}
	//	左キーが押されたとき
	else if (g_keyTracker->pressed.Left)
	{
		//	選択部分の移動
		m_sceneFlag--;

		//	シーンフラグが無いとき
		if (m_sceneFlag < 0) {
			//	エンド選択に戻る
			m_sceneFlag = SCENE_FLAG::END_FLAG;
		}
	}

	//	Enterキーが押されたとき
	else if (g_keyTracker->pressed.Enter)
	{
		//	効果音
		ADX2Le::Play(CRI_CUESHEET_0_PUSH_KEY);

		//	シーンフラグ
		switch (m_sceneFlag)
		{
		case SCENE_FLAG::PLAY_FLAG:
			//	プレイシーンに移動
			m_NextScene = PLAY;
			break;
		case SCENE_FLAG::STORY_FLAG:
			//	物語シーンに移動
			m_NextScene = STORY;
			break;
		case SCENE_FLAG::RANK_FLAG:
			//	ランキングシーンに移動
			m_NextScene = RANKING;
			break;
		case SCENE_FLAG::END_FLAG:
			//	ゲームを終了する
			PostQuitMessage(0);
			break;
		}
	}

	return m_NextScene;
}

void GameTitle::RenderGame()
{
	//	スプライトの描画========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	m_spriteBatch->Draw(m_texture.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
	
	//	選択部分
	switch (m_sceneFlag)
	{
	case SCENE_FLAG::PLAY_FLAG:
		m_spriteBatch->Draw(m_serectTexture.Get(), Vector2(45, 305), nullptr, Colors::White, 0.f, m_origin);
		break;
	case SCENE_FLAG::STORY_FLAG:
		m_spriteBatch->Draw(m_serectTexture.Get(), Vector2(222, 435), nullptr, Colors::White, 0.f, m_origin);
		break;
	case SCENE_FLAG::RANK_FLAG:
		m_spriteBatch->Draw(m_serectTexture.Get(), Vector2(461, 435), nullptr, Colors::White, 0.f, m_origin);
		break;
	case SCENE_FLAG::END_FLAG:
		m_spriteBatch->Draw(m_serectTexture.Get(), Vector2(642, 305), nullptr, Colors::White, 0.f, m_origin);
		break;
	}

	m_spriteBatch->End();
	//==========================================================================================

}

