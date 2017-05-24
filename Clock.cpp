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

	//	先端座標
	m_longTipPos = Vector2(0.0f, 0.0f);
	m_shortTipPos = Vector2(0.0f, 0.0f);

	//	回転
	m_rotLongPos = 0.0f;	//長針回転
	m_rotShortPos = 3.15f;	//短針回転

	//	座標角度
	m_LTPos = 270.0f;		//長針座標角度
	m_STPos = 90.0f;		//短針座標角度

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

	//	短針画像
	ComPtr<ID3D11Resource> shortTipRes;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/shortTip.png",
			shortTipRes.GetAddressOf(),
			m_ShortTipTex.ReleaseAndGetAddressOf()));

	//	原点画像
	ComPtr<ID3D11Resource> OriginRes;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/origin.png",
			OriginRes.GetAddressOf(),
			m_OriginTex.ReleaseAndGetAddressOf()));

	//	リソースから時計のテクスチャと判断
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(clockRes.As(&clock));

	////	リソースから長針のテクスチャと判断
	//ComPtr<ID3D11Texture2D> longTip;
	//DX::ThrowIfFailed(clockRes.As(&longTip));

	////	リソースから原点のテクスチャと判断
	//ComPtr<ID3D11Texture2D> originTip;
	//DX::ThrowIfFailed(clockRes.As(&originTip));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);

	////	テクスチャ情報
	//CD3D11_TEXTURE2D_DESC longTipDesc;
	//longTip->GetDesc(&longTipDesc);

	////	テクスチャ情報
	//CD3D11_TEXTURE2D_DESC originDesc;
	//originTip->GetDesc(&originDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(clockDesc.Width / 2.0f);
	m_origin.y = float(clockDesc.Height / 2.0f);

	//	テクスチャ原点を画像の中心にする
	//m_longTOri.x = float(longTipDesc.Width / 2.0f);
	//m_longTOri.y = float(longTipDesc.Height / 1.2f);
	//m_longTOri.x = float(longTipDesc.Width / 2.0f);
	//m_longTOri.y = float(longTipDesc.Height / 1.0f);

	////	テクスチャ原点を画像の中心にする
	//m_ori.x = float(originDesc.Width / 2.0f);
	//m_ori.y = float(originDesc.Height / 2.0f);

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
//	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f - 40.0f;

	//	表示座標を画面中央に指定
	//m_longTPos.x = m_deviceResources->GetOutputSize().right / 1.16f;
	//m_longTPos.y = m_deviceResources->GetOutputSize().bottom / 3.8f;
//	m_longTPos.x = m_deviceResources->GetOutputSize().right / 2.0f;	//2.03
//	m_longTPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;	//2.05

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
	this->clockwise();
}

//==================================//
//内容		描画
//引数		なし
//戻り値	なし
//==================================//
void Clock::Render()
{
	//	スプライトの描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	//	時計
	m_spriteBatch->Draw(m_clockTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
	//	長針
	m_spriteBatch->Draw(m_LongTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotLongPos);
	//	短針
	m_spriteBatch->Draw(m_ShortTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotShortPos);
	//	原点
	m_spriteBatch->Draw(m_OriginTex.Get(), m_screenPos+Vector2(-30.0f,-35.0f), nullptr, Colors::White, 0.f);
	m_spriteBatch->End();
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
//内容		針の原点を取得する
//引数		なし
//戻り値	針の原点(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getLongTipOrigin()
{
	return m_screenPos;
}

//==================================//
//内容		長針の先端座標取得
//引数		なし
//戻り値	先端座標(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getLongTipPos()
{
	//	長針角度
	float m_longTipAng;

	//	回転角度の取得
	m_longTipAng = XMConvertToRadians(m_LTPos);
	//	三角関数
	m_longTipPos = Vector2(ORIGINE_X + (RADIUS * cosf(m_longTipAng)), ORIGINE_Y + (RADIUS * sinf(m_longTipAng)));

	return m_longTipPos;
}

//==================================//
//内容		短針の先端座標取得
//引数		なし
//戻り値	先端座標(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getShortTipPos()
{
	//	短針角度
	float m_shortTipAng;

	//	回転角度の取得
	m_shortTipAng = XMConvertToRadians(m_STPos);

	m_shortTipPos = Vector2(ORIGINE_X + (RADIUS * cosf(m_shortTipAng)), ORIGINE_Y + (RADIUS * sinf(m_shortTipAng)));

	return m_shortTipPos;
}

//==================================//
//内容		時計回りに針を回転させる
//引数		なし
//戻り値	なし
//==================================//
void Clock::clockwise()
{
	//	回転させる
	m_rotLongPos += 0.05f;
	m_rotShortPos += 0.005f;

	//	先端座標角度が360度以内のとき
	if (m_LTPos <= 360.0f) {
		//	先端座標の角度を減らす
		m_LTPos += 0.01f;
	}
	else {
		m_LTPos = 0.0f;
	}

	//	先端座標角度が360度以内のとき
	if (m_STPos <= 360.0f) {
		//	先端座標の角度を減らす
		m_STPos += 0.01f;
	}
	else {
		m_STPos = 0.0f;
	}

}

//=============================================================//
//内容		長針と短針の間の角度算出(3点からなす角を求める)
//引数		長針先端座標(Vec2)、短針先端座標(Vec2)
//戻り値	なす角(float)
//=============================================================//
float Clock::calAngle()
{
	//	長針の長さ
	Vector2 longLeng = m_longTipPos - Vector2(ORIGINE_X, ORIGINE_Y);
	//	短針の長さ
	Vector2 shortLeng = m_shortTipPos - Vector2(ORIGINE_X, ORIGINE_Y);

	//	分子
	float numer = longLeng.x * shortLeng.x + longLeng.y * shortLeng.y;
	//	分母
	float denom = sqrtf(longLeng.x * longLeng.x + longLeng.y * longLeng.y)*
		sqrtf(shortLeng.x * shortLeng.x + shortLeng.y * shortLeng.y);

	//	cosθを求める
	float cosTheta = numer / denom;
	//	なす角(θ)に変換
	float angle = acosf(cosTheta);

	return angle;
}

