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

const float ORIGINE_X = 400.0f;
const float ORIGINE_Y = 300.0f;
const float RADIUS = 310.0f;

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

	m_rotPos = 270.0f;	//回転
	m_longTipPos = Vector2(0.0f, 0.0f);
	m_LTPos = 270.0f;

	//	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//	時計画像
	ComPtr<ID3D11Resource> clockRes;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/clock.png",
			clockRes.GetAddressOf(),
			m_clockTex.ReleaseAndGetAddressOf()));

	//	長針画像
	ComPtr<ID3D11Resource> LongTipRes;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/longTip.png",
			LongTipRes.GetAddressOf(),
			m_LongTipTex.ReleaseAndGetAddressOf()));

	//	原点画像
	ComPtr<ID3D11Resource> OriginRes;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/origin.png",
			OriginRes.GetAddressOf(),
			m_OriginTex.ReleaseAndGetAddressOf()));

	//	リソースから時計のテクスチャと判断
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(clockRes.As(&clock));

	//	リソースから長針のテクスチャと判断
	ComPtr<ID3D11Texture2D> longTip;
	DX::ThrowIfFailed(clockRes.As(&longTip));

	//	リソースから原点のテクスチャと判断
	ComPtr<ID3D11Texture2D> originTip;
	DX::ThrowIfFailed(clockRes.As(&originTip));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC longTipDesc;
	longTip->GetDesc(&longTipDesc);

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC originDesc;
	originTip->GetDesc(&originDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(clockDesc.Width / 2.0f);
	m_origin.y = float(clockDesc.Height / 2.0f);

	//	テクスチャ原点を画像の中心にする
	m_longTOri.x = float(longTipDesc.Width / 2.0f);
	m_longTOri.y = float(longTipDesc.Height / 1.2f);

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	//	表示座標を画面中央に指定
	m_longTPos.x = m_deviceResources->GetOutputSize().right / 1.16f;
	m_longTPos.y = m_deviceResources->GetOutputSize().bottom / 3.8f;

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
	//	時計を回転
	clockwise();

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
	
	//	時計
	m_spriteBatch->Draw(m_clockTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	//	長針
	//m_spriteBatch->Draw(m_LongTipTex.Get(), m_longTPos, nullptr, Colors::White, m_headPos, m_longTOri);
	m_spriteBatch->Draw(m_LongTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotPos);

	//	原点
	m_spriteBatch->Draw(m_OriginTex.Get(), m_screenPos+Vector2(-35.0f,-35.0f), nullptr, Colors::White, 0.f);

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
	float m_longTipAng;	//	長針角度

	//	回転角度の取得
	m_longTipAng = XMConvertToRadians(m_LTPos);

	m_longTipPos = Vector2(ORIGINE_X + (RADIUS * cosf(m_longTipAng)), ORIGINE_Y + (RADIUS * sinf(m_longTipAng)));

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
	//	回転させる
	m_rotPos += 0.01f;

	//	先端座標角度が360度以内のとき
	if (m_LTPos <= 360.0f) {
		//	先端座標の角度を減らす
		m_LTPos += 0.01f;
	}
	else {
		m_LTPos = 0.0f;
	}

}

DirectX::SimpleMath::Vector2 Clock::getLongTipOrigin()
{
	return m_longTOri;
}

