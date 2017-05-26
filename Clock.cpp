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

//デバック用
#include <Windows.h>
#include <Windef.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

const float ORIGINE_X = 450.0f;
const float ORIGINE_Y = 310.0f;
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
	m_rotLongPos = 3.15f;	//長針回転
	m_rotShortPos = 3.15f;	//短針回転

	//	座標角度
//	m_LTPos = 0.0f;		//長針座標角度
//	m_STPos = 0.0f;		//短針座標角度

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
	//	時計
	ComPtr<ID3D11Texture2D> clock;
	DX::ThrowIfFailed(clockRes.As(&clock));
	//	長針
	ComPtr<ID3D11Texture2D> longTip;
	DX::ThrowIfFailed(LongTipRes.As(&longTip));
	//	短針
	ComPtr<ID3D11Texture2D> shortTip;
	DX::ThrowIfFailed(shortTipRes.As(&shortTip));
	//	原点
	ComPtr<ID3D11Texture2D> originTip;
	DX::ThrowIfFailed(OriginRes.As(&originTip));

	//	テクスチャ情報
	//	時計
	CD3D11_TEXTURE2D_DESC clockDesc;
	clock->GetDesc(&clockDesc);
	//	長針
	CD3D11_TEXTURE2D_DESC longTipDesc;
	longTip->GetDesc(&longTipDesc);
	//	短針
	CD3D11_TEXTURE2D_DESC shortTipDesc;
	shortTip->GetDesc(&shortTipDesc);
	//	原点
	CD3D11_TEXTURE2D_DESC originDesc;
	originTip->GetDesc(&originDesc);

	//	テクスチャ原点を画像の中心にする
	//	時計
	m_origin.x = float(clockDesc.Width / 2.0f);
	m_origin.y = float(clockDesc.Height / 2.0f);
	//	長針
	m_longTOri.x = float(longTipDesc.Width / 2.0f);
	m_longTOri.y = float(longTipDesc.Height / 1.0f);
	//	短針
	m_shortTOri.x = float(shortTipDesc.Width / 2.0f);
	m_shortTOri.y = float(shortTipDesc.Height / 1.0f);
	//	原点
	m_ori.x = float(originDesc.Width / 2.0f);
	m_ori.y = float(originDesc.Height / 2.0f);

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f - 40.0f;

	//==========================================================================================
	//通常時画像
	ComPtr<ID3D11Resource> time_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/number.png",
			time_resource.GetAddressOf(),
			m_time_tex.ReleaseAndGetAddressOf()));

	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> time;
	DX::ThrowIfFailed(time_resource.As(&time));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC timeDesc;
	time->GetDesc(&timeDesc);

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
	m_spriteBatch->Draw(m_LongTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotLongPos, m_longTOri);
	//	短針
	m_spriteBatch->Draw(m_ShortTipTex.Get(), m_screenPos, nullptr, Colors::White, m_rotShortPos, m_shortTOri);
	//	原点
	m_spriteBatch->Draw(m_OriginTex.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_ori);
	m_spriteBatch->End();

	//デバック用数値描画
	//DrawNum(100, 80, (int)m_longTipPos.x);
	//DrawNum(100, 100, (int)m_longTipPos.y);

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
DirectX::SimpleMath::Vector2 Clock::getOrigin()
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
	Vector2 position;

	position.x = (sinf(-m_rotLongPos) * 310.0f) + 450.0f;
	position.y = (cosf(-m_rotLongPos) * 310.0f) + 310.0f;

	return position;

	////	長針角度
	//float m_longTipAng;
	////	回転角度の取得
	//m_longTipAng = XMConvertToRadians(m_LTPos);
	////	三角関数
	//m_longTipPos = Vector2(ORIGINE_X + (RADIUS * cosf(m_longTipAng)), ORIGINE_Y + (RADIUS * sinf(m_longTipAng)));
	//return m_longTipPos;
}

//==================================//
//内容		短針の先端座標取得
//引数		なし
//戻り値	先端座標(Vec2)
//==================================//
DirectX::SimpleMath::Vector2 Clock::getShortTipPos()
{
	Vector2 position;

	position.x = (sinf(-m_rotShortPos) * 198.0f) + 450.0f;
	position.y = (cosf(-m_rotShortPos) * 198.0f) + 310.0f;

	return position;

	////	短針角度
	//float m_shortTipAng;
	////	回転角度の取得
	//m_shortTipAng = XMConvertToRadians(m_STPos);
	//m_shortTipPos = Vector2(ORIGINE_X + (RADIUS * cosf(m_shortTipAng)), ORIGINE_Y + (RADIUS * sinf(m_shortTipAng)));
	//return m_shortTipPos;
}

//==================================//
//内容		長針の回転角度取得
//引数		なし
//戻り値	角度(float)
//==================================//
float Clock::getRotLong()
{
	return m_rotLongPos;
}

//==================================//
//内容		短針の回転角度取得
//引数		なし
//戻り値	角度(float)
//==================================//
float Clock::getRotShort()
{
	return m_rotShortPos;
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

	////	先端座標角度が360度以内のとき
	//if (m_LTPos <= 360.0f) {
	//	//	先端座標の角度を減らす
	//	m_LTPos += 0.01f;
	//}
	//else {
	//	m_LTPos = 0.0f;
	//}

	////	先端座標角度が360度以内のとき
	//if (m_STPos <= 360.0f) {
	//	//	先端座標の角度を減らす
	//	m_STPos += 0.01f;
	//}
	//else {
	//	m_STPos = 0.0f;
	//}

}


////=============================================================//
////内容		3点の座標からなす角の算出
////引数		原点(Vec2)、長針先端座標(Vec2)、短針先端座標(Vec2)
////戻り値	なす角(float)
////=============================================================//
//float Clock::calAngle(Vector2 origin, Vector2 longTip, Vector2 shortTip)
//{
//	//	原点からlongTipまでの長さ
//	Vector2 longLeng = longTip - origin;
//	//	原点からshortTipまでの長さ
//	Vector2 shortLeng = shortTip - origin;
//
//	//	分子
//	float numer = longTip.x * shortTip.x + longTip.y * shortTip.y;
//	//	分母
//	float denom = sqrtf(longTip.x * longTip.x + longTip.y * longTip.y)*
//		sqrtf(shortTip.x * shortTip.x + shortTip.y * shortTip.y);
//
//	//	cosθを求める
//	float cosTheta = numer / denom;
//	//	なす角(θ)に変換
//	float angle = acosf(cosTheta);
//
//	return angle;
//}

//∞------------------------------------------------------------------∞
//∞*func：時間描画関数
//∞*arg：描画位置(float x、float y)、描画する数値(int n)
//∞*return：なし
//∞------------------------------------------------------------------∞
void Clock::DrawNum(float x, float y, int n)
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	int w = n;		//作業用
	int i = 0;		//文字数

	RECT rect;

	if (w == 0)
	{
		rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };

		m_spriteBatch->Draw(m_time_tex.Get(), Vector2(x, y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

		//DrawRectGraph(x, y, 0, 48, 25, 32, g_PongImage, TRUE, FALSE);
	}

	else
	{
		while (w)
		{
			m_grpX = (w % 10) * 25;
			rect = { (LONG)0, (LONG)48, (LONG)(m_grpX + 25), (LONG)(48 + 32) };
			m_spriteBatch->Draw(m_time_tex.Get(), Vector2((x - i * 25), y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

			//DrawRectGraph(x - i * 25, y, (w % 10) * 25, 48, 25, 32, g_PongImage, TRUE, FALSE);
			w = w / 10;
			i++;
		}
	}

	m_spriteBatch->End();
}


