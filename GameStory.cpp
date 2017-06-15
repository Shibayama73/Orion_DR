//∞----------------------------------------------------∞
//∞*ファイル名：GameStory.cpp							∞
//∞*内容　　　：ストーリー解説シーン					∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.06.15								∞
//∞----------------------------------------------------∞
#include "pch.h"
#include "GameStory.h"
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


GameStory::GameStory()
{
	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/howto1.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/howto2.png",
			resource.GetAddressOf(),
			m_texture2.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/howto3.png",
			resource.GetAddressOf(),
			m_texture3.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/howto4.png",
			resource.GetAddressOf(),
			m_texture4.ReleaseAndGetAddressOf()));

	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(resource.As(&clock));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = 0.0;
	m_origin.y = 0.0;

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//==========================================================================================
	
	//	サウンドファイルの読み込み
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

	//	サウンド再生
	ADX2Le::Play(CRI_CUESHEET_0_STORY);
	
	m_page = 0;
}


GameStory::~GameStory()
{
	//	サウンドライブラリの終了処理
	ADX2Le::Finalize();
}

int GameStory::UpdateGame()
{
	m_NextScene = STORY;
	m_scene = STORY;

	//	サウンドの更新
	ADX2Le::Update();

	if (g_keyTracker->pressed.Enter)
	{
		//	効果音
		ADX2Le::Play(CRI_CUESHEET_0_PAGE);

		m_page++;
		if (m_page > 3)
		{
			m_NextScene = TITLE;
		}
	}

	return m_NextScene;
}

void GameStory::RenderGame()
{
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	switch (m_page)
	{
	case 0:
		m_spriteBatch->Draw(m_texture.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
		break;
	case 1:
		m_spriteBatch->Draw(m_texture2.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
		break;
	case 2:
		m_spriteBatch->Draw(m_texture3.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
		break;
	case 3:
		m_spriteBatch->Draw(m_texture4.Get(), Vector2(0, 0), nullptr, Colors::White, 0.f, m_origin);
		break;
	}

	m_spriteBatch->End();

}
