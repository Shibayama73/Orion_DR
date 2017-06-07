//∞----------------------------------------------------∞
//∞*ファイル名：Effect.cpp								∞
//∞*内容　　　：エフェクトクラス						∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.06.05								∞
//∞----------------------------------------------------∞

#include "pch.h"
#include "Effect.h"

#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>
#include <Math.h>

#include "Game.h"
#include "pch.h"
#include <WICTextureLoader.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


//∞------------------------------------------------------------------∞
//∞*func：コンストラクタ
//∞*arg：なし
//∞------------------------------------------------------------------∞
Effect::Effect()
{
	m_state = EFFECT_OFF;

	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//エフェクト用画像
	ComPtr<ID3D11Resource> effect_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/kirakira.png",
			effect_resource.GetAddressOf(),
			m_effect_tex.ReleaseAndGetAddressOf()));


	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> effect;
	DX::ThrowIfFailed(effect_resource.As(&effect));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC effectDesc;
	effect->GetDesc(&effectDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(effectDesc.Width / 2.0f);
	m_origin.y = float(effectDesc.Height / 2.0f);

	m_cnt = 0;
}


//∞------------------------------------------------------------------∞
//∞*func：デストラクタ
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞

Effect::~Effect()
{
}

//∞------------------------------------------------------------------∞
//∞*func：更新関数
//∞*arg：なし
//∞*return：なし
//∞*heed：なし
//∞------------------------------------------------------------------∞

void Effect::Update()
{
	//エフェクトがONの時
	if (m_state == EFFECT_ON)
	{
		m_cnt++;
		//60フレーム経ったら消失
		if (m_cnt > 60)
		{
			EffectLoss();
		}
	}
}


//∞------------------------------------------------------------------∞
//∞*func：描画関数
//∞*arg：なし
//∞*return：なし
//∞*heed：なし
//∞------------------------------------------------------------------∞

void Effect::Render()
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	if (m_state == EFFECT_ON)
	{
   		m_spriteBatch->Draw(m_effect_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
		m_spriteBatch->Draw(m_effect_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
	}
	m_spriteBatch->End();

}

//∞------------------------------------------------------------------∞
//∞*func：エフェクトのstateをonにする関数
//∞*arg：欠片の位置(float posX,float posY)
//∞*return：なし
//∞------------------------------------------------------------------∞

void Effect::ChengeState(float posX, float posY)
{
	m_posX = posX;
	m_posY = posY;

	m_state = EFFECT_ON;
}

//∞------------------------------------------------------------------∞
//∞*func：エフェクトのstateをlossにする関数
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
void Effect::EffectLoss()
{
	m_state = EFFECT_LOSS;
}

//∞------------------------------------------------------------------∞
//∞*func：エフェクトのstateを取得する関数
//∞*arg：なし
//∞*return：m_state
//∞------------------------------------------------------------------∞
int Effect::State()
{
	return m_state;
}


