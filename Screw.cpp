//∞----------------------------------------------------∞
//∞*ファイル名：Screw.cpp								∞
//∞*内容　　　：ネジクラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.06.01								∞
//∞----------------------------------------------------∞


#include "pch.h"
#include "Screw.h"

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

Screw::Screw()
{
	m_posX = rand() % 470 + 200;
	m_posY = (rand() % -1000) - 1010;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpW = 64;
	m_grpH = 64;



	m_state = SCREW_NORMAL;

	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//通常時画像
	ComPtr<ID3D11Resource> screw_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/bolt.png",
			screw_resource.GetAddressOf(),
			m_screw_tex.ReleaseAndGetAddressOf()));

	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> screw;
	DX::ThrowIfFailed(screw_resource.As(&screw));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC screwDesc;
	screw->GetDesc(&screwDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(screwDesc.Width / 2.0f);
	m_origin.y = float(screwDesc.Height / 2.0f);

}

//∞------------------------------------------------------------------∞
//∞*func：デストラクタ
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
Screw::~Screw()
{
}

//∞------------------------------------------------------------------∞
//∞*func：更新処理
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
void Screw::Update()
{
	m_spdY += 0.02;
	m_posY += m_spdY;
	m_posX += m_spdX;


	//場外に出ているかの判定
	Outdoor();
}

//∞------------------------------------------------------------------∞
//∞*func：描画処理
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
void Screw::Render()
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	m_spriteBatch->Draw(m_screw_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);


	m_spriteBatch->End();

}

//∞------------------------------------------------------------------∞
//∞*func：画面内に欠片があるかどうか
//∞*arg：なし
//∞*return：true（ある）、false（ない）
//∞------------------------------------------------------------------∞
void Screw::Outdoor()
{
	if (m_posY + m_grpH > 700)
	{
		m_state = SCREW_LOSS;
	}

}

//∞------------------------------------------------------------------∞
//∞*func：当たり判定
//∞*arg：比較するオブジェクト
//∞*return：true（当たっている）、false（当たっていない）
//∞------------------------------------------------------------------∞
//反射判定
bool Screw::Collision(ObjectBase* A)
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
		m_state = SCREW_LOSS;
		return true;
	}
	return false;
}

//∞------------------------------------------------------------------∞
//∞*func：状態を取得する
//∞*arg：なし
//∞*return：m_state
//∞------------------------------------------------------------------∞
int Screw::State()
{
	return m_state;
}
