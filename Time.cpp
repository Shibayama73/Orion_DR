//∞----------------------------------------------------∞
//∞*ファイル名：Time.cpp								∞
//∞*内容　　　：時間クラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.25 							∞
//∞----------------------------------------------------∞

#include "pch.h"
#include "Time.h"

#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

#include "Game.h"
#include "pch.h"
#include <Windows.h>
#include <Windef.h>
#include <WICTextureLoader.h>



using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace std;

//制限時間
const int TIME_MAX = 72;


//∞------------------------------------------------------------------∞
//∞*func：コンストラクタ
//∞*arg：なし
//∞------------------------------------------------------------------∞
Time::Time()
{
	//数値の初期化
	//m_current_time = 0;
	m_current_time = 70;

	m_remnant_time = 10;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 26.0f;
	m_grpH = 32.0f;
	m_posX = 0.0f;
	m_posY = 0.0f;

	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//通常時画像
	ComPtr<ID3D11Resource> time_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/number2.png",
			time_resource.GetAddressOf(),
			m_time_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/remaining.png",
			time_resource.GetAddressOf(),
			m_remaining_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/time.png",
			time_resource.GetAddressOf(),
			m_h_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/now.png",
			time_resource.GetAddressOf(),
			m_now_tex.ReleaseAndGetAddressOf()));

	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> time;
	DX::ThrowIfFailed(time_resource.As(&time));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC timeDesc;
	time->GetDesc(&timeDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(timeDesc.Width / 2.0f);
	m_origin.y = float(timeDesc.Height / 2.0f);


}
Time::~Time()
{	
}


//∞------------------------------------------------------------------∞
//∞*func：描画関数
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
void Time::Render()
{
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	m_spriteBatch->Draw(m_remaining_tex.Get(), Vector2(100, 185), nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_now_tex.Get(), Vector2(100, 65), nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_h_tex.Get(), Vector2(180, 105), nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_h_tex.Get(), Vector2(180, 225), nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();

	//現在の時間表示
	DrawNum(100, 90, m_current_time - 1);

	//残りの時間表示
	DrawNum(100, 210, m_remnant_time);


}

//∞------------------------------------------------------------------∞
//∞*func：現在の時間の取得
//∞*arg：なし
//∞*return：なし
//∞*heed：長針がpos(450,0)になったら呼び出す
//∞------------------------------------------------------------------∞
void Time::CurrentTime()
{
	m_current_time++;
}

//∞------------------------------------------------------------------∞
//∞*func：残りの時間計算関数
//∞*arg：なし
//∞*return：残り時間がある(true)か、ないか(false)
//∞*heed：falseを返したら、容赦なくゲームオーバ
//∞------------------------------------------------------------------∞
bool Time::RemnantTime()
{
	if (m_remnant_time != 0)
	{
		//制限時間-今の時間を残りの時間にする
		m_remnant_time = TIME_MAX - (m_current_time-1);
		if (m_remnant_time > TIME_MAX)
		{
			m_remnant_time = TIME_MAX;
		}
		return true;
	}
	else
	{
		return false;
	}
}

//∞------------------------------------------------------------------∞
//∞*func：時間描画関数
//∞*arg：描画位置(float x、float y)、描画する数値(int n)
//∞*return：なし
//∞------------------------------------------------------------------∞
void Time::DrawNum(float x, float y, int n)
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	int w = n;		//作業用
	int i = 0;		//文字数

	RECT rect;

	if (w < 0)
	{
		rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };

		m_spriteBatch->Draw(m_time_tex.Get(), Vector2(x, y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

		//DrawRectGraph(x, y, 0, 48, 25, 32, g_PongImage, TRUE, FALSE);
	}

	else
	{
		while (w)
		{
			m_grpX = (w % 10) * m_grpW;
			rect = {(LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
			m_spriteBatch->Draw(m_time_tex.Get(), Vector2((x - i * m_grpW), y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

			w = w / 10;
			i++;
		}
	}

	m_spriteBatch->End();
}
