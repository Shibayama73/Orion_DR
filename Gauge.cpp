//**********************************//
//*	名　前：Gauge.cpp
//*	内　容：欠片計量ゲージクラス
//*	日　付：2017.05.24
//* 更新日：2017.06.02
//*	制作者：N.Shibayama
//**********************************//

#include "Gauge.h"
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
Gauge::Gauge()
{
	//	初期化
	m_gradation = 0;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpX = 115.0f;	//115
	m_grpY = 550.0f;	//571
	m_grpW = -115.0f;
	m_grpH = -7.0f;		//1個につきのゲージ分縦幅(調整必須)
	m_posX = 0.0f;
	m_posY = 0.0f;

	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//	砂時計画像
	ComPtr<ID3D11Resource> hourglassResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/gauge1.png",
			hourglassResource.GetAddressOf(),
			m_hourglassTex.ReleaseAndGetAddressOf()));

	//	ゲージ色画像
	ComPtr<ID3D11Resource> colorResource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/gauge2.png",
			colorResource.GetAddressOf(),
			m_colorTex.ReleaseAndGetAddressOf()));

	//	リソースからテクスチャと判断
	//	砂時計
	ComPtr<ID3D11Texture2D> hourglass;
	DX::ThrowIfFailed(hourglassResource.As(&hourglass));
	//	ゲージ色
	ComPtr<ID3D11Texture2D> gradation;
	DX::ThrowIfFailed(colorResource.As(&gradation));

	//	テクスチャ情報
	//	砂時計
	CD3D11_TEXTURE2D_DESC hourglassDesc;
	hourglass->GetDesc(&hourglassDesc);
	//	ゲージ色
	CD3D11_TEXTURE2D_DESC gradationDesc;
	gradation->GetDesc(&gradationDesc);

	//	テクスチャ原点(右下)の指定
	//	砂時計
	m_origin.x = float(hourglassDesc.Width / 1.0f);
	m_origin.y = float(hourglassDesc.Height / 1.0f);
	//	ゲージ色
	m_gradationOrigin.x = float(gradationDesc.Width / 1.0f);
	m_gradationOrigin.y = float(gradationDesc.Height / 1.0f);

	//	表示座標の指定
	//	砂時計
	m_screenPos.x = m_deviceResources->GetOutputSize().right - 10.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom - 50.0f;
	//	ゲージ色
	/*m_gradationPos.x = m_deviceResources->GetOutputSize().right - 10.0f;
	m_gradationPos.y = m_deviceResources->GetOutputSize().bottom - 50.0f;*/
	m_gradationPos.x = m_deviceResources->GetOutputSize().right + m_grpX - 10.0f;
	m_gradationPos.y = m_deviceResources->GetOutputSize().bottom + m_grpY - 50.0f;
	
}

//==================================//
//内容		デストラクタ
//引数		なし
//戻り値	なし
//==================================//
Gauge::~Gauge()
{
}

//==================================//
//内容		更新
//引数		なし
//戻り値	なし
//==================================//
void Gauge::Update()
{
}

//==================================//
//内容		描画
//引数		なし
//戻り値	なし
//==================================//
void Gauge::Render()
{
	//	スプライトの描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());
	//	砂時計
	m_spriteBatch->Draw(m_hourglassTex.Get(), m_screenPos, nullptr, Colors::White, 0.0f, m_origin);
	//	ゲージ色
	RECT rect;
	if (m_gradation)
	{
	//	m_gradation = (m_gradation % 14) * m_grpW;
		//rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
		rect = { (LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + (m_grpH * m_gradation)) };
		//	ゲージ色の描画
		m_spriteBatch->Draw(m_colorTex.Get(), m_gradationPos, &rect, Colors::White, 0.0f, m_gradationOrigin);

	//	m_gradation = m_gradation / 14;
	}

	m_spriteBatch->End();
}

//=================================================================================//
//内容		ゲージの値を加算する
//引数		欠片の状態(int)
//戻り値	なし
//※前提としてこの関数は掴まれた状態から消えた状態のときに使用されるものとする
//=================================================================================//
void Gauge::addGradation(int state)
{
	//	stateが消えた状態のとき
	if (state == FRAGMENT_LOSS)
	{
		//	値を加算する
		m_gradation++;
	}

}

//==================================//
//内容		ゲージの値を取得する
//引数		なし
//戻り値	ゲージの値(int)
//==================================//
int Gauge::getGradation()
{
	return m_gradation;
}
