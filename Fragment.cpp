//∞----------------------------------------------------∞
//∞*ファイル名：Fragment.cpp							∞
//∞*内容　　　：欠片クラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.22 							∞
//∞----------------------------------------------------∞


#include "pch.h"
#include "Fragment.h"

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
Fragment::Fragment()
{
	m_posX = rand() % 470 + 200;
	m_posY = (rand() % -1000) - 1010;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpW = 32;
	m_grpH = 32;

	m_state = FRAGMENT_NORMAL;

	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//通常時画像
	ComPtr<ID3D11Resource> fragment_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/star.png",
			fragment_resource.GetAddressOf(),
			m_fragment_tex.ReleaseAndGetAddressOf()));
	//キャッチ後画像
	ComPtr<ID3D11Resource> fragment_catch_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/star_catch.png",
			fragment_catch_resource.GetAddressOf(),
			m_fragment_catch_tex.ReleaseAndGetAddressOf()));


	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> fragment;
	DX::ThrowIfFailed(fragment_resource.As(&fragment));
	DX::ThrowIfFailed(fragment_catch_resource.As(&fragment));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC fragmentDesc;
	fragment->GetDesc(&fragmentDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(fragmentDesc.Width / 2.0f);
	m_origin.y = float(fragmentDesc.Height / 2.0f);


}


//∞------------------------------------------------------------------∞
//∞*func：デストラクタ
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
Fragment::~Fragment()
{
}

//∞------------------------------------------------------------------∞
//∞*func：更新処理
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
void Fragment::Update(DirectX::SimpleMath::Vector2 origin)
{
	m_spdY += 0.01;
	m_posY += m_spdY;
	m_posX += m_spdX;

	if (m_state == FRAGMENT_CATCH)
	{
		if (origin.y > m_posY)
		{
			m_spdY = 0.1f;
		}
		else if (origin.y < m_posY)
		{
			m_spdY = -0.1f;
		}
		else
		{
			m_spdX = 0;
			m_spdY = 0;
		}
	}


	//場外に出ているかの判定
	Outdoor();
}

//∞------------------------------------------------------------------∞
//∞*func：描画処理
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
void Fragment::Render()
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	switch (m_state)
	{
	case FRAGMENT_NORMAL:
		m_spriteBatch->Draw(m_fragment_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
		break;

	case FRAGMENT_CATCH:
		m_spriteBatch->Draw(m_fragment_catch_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
		break;
	}
	

	m_spriteBatch->End();

}

//∞------------------------------------------------------------------∞
//∞*func：画面内に欠片があるかどうか
//∞*arg：なし
//∞*return：true（ある）、false（ない）
//∞------------------------------------------------------------------∞
void Fragment::Outdoor()
{
	if (m_posY + m_grpH > 700)
	{
		m_state = FRAGMENT_LOSS;
	}

}

//∞------------------------------------------------------------------∞
//∞*func：表示情報の取得関数（m_state）
//∞*arg：なし
//∞*return：m_state
//∞------------------------------------------------------------------∞
int Fragment::State()
{
	return m_state;
}

//∞------------------------------------------------------------------∞
//∞*func：当たり判定
//∞*arg：比較するオブジェクト
//∞*return：true（当たっている）、false（当たっていない）
//∞------------------------------------------------------------------∞
//反射判定
bool Fragment::Collision(ObjectBase* A)
{
	float x1 = m_posX + m_grpW / 2;
	float y1 = m_posY + m_grpH / 2;
	float x2 = A->GetPosX() + A->GetGrpW() / 2;
	float y2 = A->GetPosY() + A->GetGrpH() / 2;
	float r1 = m_grpW / 2;
	float r2 = A->GetGrpW() / 2;

	//円のあたり判定
	if ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) <= (r1 + r2)*(r1 + r2))
	{
		//欠片が通常状態なら当たっている
		if (m_state == FRAGMENT_NORMAL)
		{
			m_state = FRAGMENT_CATCH;
			return true;
		}
	}
	return false;
}


