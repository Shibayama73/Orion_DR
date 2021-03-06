//∞----------------------------------------------------∞
//∞*ファイル名：Wire.cpp								∞
//∞*内容　　　：ワイヤー								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.18								∞
//∞----------------------------------------------------∞

#include "pch.h"
#include "Wire.h"

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

//∞------------------------------------------------------------------∞
//∞*func：コンストラクタ
//∞*arg：なし
//∞------------------------------------------------------------------∞
Wire::Wire(float posX)
{

	m_state = true;		//表示状態
	m_posX = posX;
	m_posY = 600;

	m_grpH = 64.0f;
	m_grpW = 64.0f;
	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//通常時画像
	ComPtr<ID3D11Resource> wire_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/wire.png",
			wire_resource.GetAddressOf(),
			m_wire_tex.ReleaseAndGetAddressOf()));



	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> wire;
	DX::ThrowIfFailed(wire_resource.As(&wire));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC wireDesc;
	wire->GetDesc(&wireDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(wireDesc.Width / 2.0f);
	m_origin.y = float(wireDesc.Height / 2.0f);



}

//∞------------------------------------------------------------------∞
//∞*func：デストラクタ
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
Wire::~Wire()
{
}

//∞------------------------------------------------------------------∞
//∞*func：更新
//∞*arg：プレイヤーの座標x
//∞*return：なし
//∞------------------------------------------------------------------∞
void Wire::Update(float pos_x)
{
	if (m_state)
	{
		m_posX = pos_x;
		//m_posY -=3;
		m_posY -= 15;

	}
	if (m_state && m_posY < 0)
	{
		Elimination();
	}
}

//∞------------------------------------------------------------------∞
//∞*func：描画関数
//∞*arg：プレイヤーの座標x
//∞*return：なし
//∞------------------------------------------------------------------∞
void Wire::Render(float pos_x)
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	if (m_state)
	{
		m_spriteBatch->Draw(m_wire_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
	}
	m_spriteBatch->End();


}

//∞------------------------------------------------------------------∞
//∞*func：消滅させる関数（m_state）
//∞*arg：なし
//∞*return：なし
//∞*heed：画面外に出たら消滅させる、もしくは、欠片をキャッチしたら
//∞------------------------------------------------------------------∞
void Wire::Elimination()
{
	m_state = false;
}

//∞------------------------------------------------------------------∞
//∞*func：表示情報の取得関数（m_state）
//∞*arg：なし
//∞*return：m_state
//∞------------------------------------------------------------------∞
bool Wire::State()
{
	return m_state;
}


