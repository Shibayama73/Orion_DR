//**********************************//
//*	名　前：Clock.cpp
//*	内　容：時計クラス
//*	日　付：2017.5.2
//*	制作者：N.Shibayama
//**********************************//

#include "Clock.h"
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

//==================================//
//内容		コンストラクタ
//引数		なし
//戻り値	なし
//==================================//
Clock::Clock()
{
	//初期化
	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 0.0f;
	m_grpH = 0.0f;
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_state = 0;


	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//	時計画像
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/clock.png",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

	//	オリオン画像
	ComPtr<ID3D11Resource> resource2;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/longTip.png",
			resource2.GetAddressOf(),
			m_texture2.ReleaseAndGetAddressOf()));

	//	リソースから時計のテクスチャと判断
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

//==================================//
//内容		デストラクタ
//引数		なし
//戻り値	なし
//==================================//
Clock::~Clock()
{
}

//==================================//
//内容		更新
//引数		なし
//戻り値	なし
//==================================//
void Clock::Update()
{
}

//==================================//
//内容		描画
//引数		なし
//戻り値	なし
//==================================//
void Clock::Render()
{
	//	スプライトの描画========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	
	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_texture2.Get(), m_screenPos+Vector2(120,0), nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();
	//==========================================================================================

}

//==================================//
//内容		針の状態取得
//引数		なし
//戻り値	長針(true)短針(false)
//==================================//
bool Clock::getHand()
{
	return m_hand;
}

//==================================//
//内容		長針の先端座標取得
//引数		なし
//戻り値	先端座標(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getLongTipPos()
{
	return m_longTipPos;
}

//==================================//
//内容		短針の先端座標取得
//引数		なし
//戻り値	先端座標(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getShotTipPos()
{
	return m_shotTipPos;
}

//==================================//
//内容		時計回りに針を回転させる
//引数		なし
//戻り値	なし
//==================================//
void Clock::clockwise()
{
	
}

