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
	m_posX = rand() % 700;
	m_posY = (rand() % -100) - 100;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpW = 32;
	m_grpH = 32;

	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//通常時画像
	ComPtr<ID3D11Resource> fragment_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/fragment.png",
			fragment_resource.GetAddressOf(),
			m_fragment_tex.ReleaseAndGetAddressOf()));

	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> fragment;
	DX::ThrowIfFailed(fragment_resource.As(&fragment));

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
void Fragment::Update()
{
	m_spdY += 0.1;
	m_posY += m_spdY;
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

	m_spriteBatch->Draw(m_fragment_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();

}

//∞------------------------------------------------------------------∞
//∞*func：画面内に欠片があるかどうか
//∞*arg：なし
//∞*return：true（ある）、false（ない）
//∞------------------------------------------------------------------∞
bool Fragment::Outdoor()
{
	if (m_posY > 640)
	{
		return false;
	}
	return true;
}
