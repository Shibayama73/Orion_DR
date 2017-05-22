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
Wire::Wire()
{

	m_state = false;		//非表示状態

	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//通常時画像
	ComPtr<ID3D11Resource> wire_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/wire.png",
			wire_resource.GetAddressOf(),
			m_wire_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/wire_L.png",
			wire_resource.GetAddressOf(),
			m_wire_L_tex.ReleaseAndGetAddressOf()));



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
//∞*func：描画関数
//∞*arg：プレイヤーの座標y
//∞*return：なし
//∞------------------------------------------------------------------∞
void Wire::Render(float pos_y, bool player_vec)
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	if (m_state)
	{
		switch (player_vec)
		{
		case LEFT:
			m_spriteBatch->Draw(m_wire_L_tex.Get(), Vector2(700, pos_y), nullptr, Colors::White, 0.f, m_origin);
			break;
		case RIGHT:
			m_spriteBatch->Draw(m_wire_tex.Get(), Vector2(700, pos_y), nullptr, Colors::White, 0.f, m_origin);
			break;
		}

	}
	m_spriteBatch->End();


}

//∞------------------------------------------------------------------∞
//∞*func：表示させる関数（m_state）
//∞*arg：なし
//∞*return：m_state
//∞*heed：ワイヤーを出す動作をしたらtrueにする。
//∞------------------------------------------------------------------∞
bool Wire::Appears()
{
	if (!m_state)
	{
		m_state = true;
	}
	return m_state;
}


