//**********************************//
//*	GamePlay.cpp
//*	プレイシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GamePlay.h"
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

GamePlay::GamePlay()
{
	//m_TimeCnt = 0;

	//	時計生成
	m_clock = new Clock();

	//プレイヤーの生成
	m_player = new Player();



	////	描画読み込み============================================================================
	//m_deviceResources = Game::m_deviceResources.get();
	//m_spriteBatch = Game::m_spriteBatch.get();

	//ComPtr<ID3D11Resource> resource;
	//DX::ThrowIfFailed(
	//	CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/clock.png",
	//		resource.GetAddressOf(),
	//		m_texture.ReleaseAndGetAddressOf()));

	////	リソースから背景のテクスチャと判断
	//ComPtr<ID3D11Texture2D> clock;
	//DX::ThrowIfFailed(resource.As(&clock));

	////	テクスチャ情報
	//CD3D11_TEXTURE2D_DESC clockDesc;
	//clock->GetDesc(&clockDesc);

	////	テクスチャ原点を画像の中心にする
	//m_origin.x = float(clockDesc.Width / 2.0f);
	//m_origin.y = float(clockDesc.Height / 2.0f);

	////	表示座標を画面中央に指定
	//m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	//m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	////==========================================================================================

}

GamePlay::~GamePlay()
{
	//	時計破棄
	delete m_clock;

	//プレイヤーの破棄
	delete m_player;
}

int GamePlay::UpdateGame()
{
	m_NextScene = PLAY;
	m_scene = PLAY;

	//	各クラスの更新
	//	時計の更新
	m_clock->Update();
	m_player->Needle(m_clock->getLongTipPos(), m_clock->getLongTipOrigin());
	//	プレイヤーの移動処理
	m_player->run(m_clock->getLongTipPos(), m_clock->getLongTipOrigin());

	//	プレイヤーの更新
	m_player->Update();

	/*m_TimeCnt++;
	if (m_TimeCnt > 120)
	{
		m_NextScene = CLEAR;
	}*/


	return m_NextScene;
}

void GamePlay::RenderGame()
{
	//	時計描画
	m_clock->Render();

	//プレイヤーの描画
	m_player->Render();


	////	スプライトの描画========================================================================
	//CommonStates m_states(m_deviceResources->GetD3DDevice());
	//m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	//m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);

	//m_spriteBatch->End();
	////==========================================================================================

}
