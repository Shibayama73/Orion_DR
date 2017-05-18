//∞----------------------------------------------------∞
//∞*ファイル名：Player.cpp								∞
//∞*内容　　　：プレイヤークラス						∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.01								∞
//∞----------------------------------------------------∞

#include "pch.h"
#include "Player.h"

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

Player::Player()
{
	//変数の初期化（値はそれぞれ仮値）
	m_posX = 10.0f;
	m_posY = 300.0f;
	m_grpW = GRP_WIDTH;
	m_grpH = GRP_HEIGHT;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	jump_flug = false;

	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//通常時画像
	ComPtr<ID3D11Resource> normal_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_normal.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_tex.ReleaseAndGetAddressOf()));


	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> orion;
	DX::ThrowIfFailed(normal_resource.As(&orion));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC orionDesc;
	orion->GetDesc(&orionDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(orionDesc.Width / 2.0f);
	m_origin.y = float(orionDesc.Height / 2.0f);


}

//∞------------------------------------------------------------------∞
//∞*func：デストラクタ
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞

Player::~Player()
{
}


//∞------------------------------------------------------------------∞
//∞*func：針の情報を取得する
//∞*arg：針の先端の座標（Vec2）
//∞*return：なし
//∞*heed：Update関数にて常に呼び出すこと
//∞------------------------------------------------------------------∞
void Player::Needle(DirectX::SimpleMath::Vector2 needle)
{
	//一次関数の傾きの指定
	//y=ax+b(原点は固定なので、bは変動しない(仮値は０））
	a = (needle.y - 0) / needle.x;
}

//∞------------------------------------------------------------------∞
//∞*func：今乗っている針の長さを取得する
//∞*arg：clock関数から長針か短針か（長針：true、短針：false）
//∞*return：長針か短針か（長針：true、短針：false）
//∞*heed：Update関数にて常に呼び出すこと
//∞------------------------------------------------------------------∞

bool Player::Length(bool length)
{

	return false;
}



//∞------------------------------------------------------------------∞
//∞*func：針の有無を確認する
//∞*arg：長針か短針か（長針：true、短針：false）
//∞*return：針があるか、ないか（ある：true、ない：false）
//∞*heed：引数は、Length()を使う。Updateで常に呼び出し
//∞------------------------------------------------------------------∞

bool Player::Existence(bool length)
{
	float needle_length = 0;	//針の長さ(三角関数のc2=a2+b2でいうc2の部分）

	switch (length)
	{
		//長針の場合
	case true:
		//針の長さを指定する
		needle_length = 20;
		break;
		//短針の場合
	case false:
		//針の長さを指定する
		needle_length = 10;
		break;
	}

	//プレイヤーの座標と、針の座標の当たり判定
	if ((m_posY > (a * m_posX + 0)) || (m_posY > (a * (m_posX + m_grpW) + 0))
		|| (m_posY + m_grpH > (a * m_posX + 0)) || (m_posY + m_grpH > (a * (m_posX + m_grpW) + 0)))
	{
		//プレイヤーの位置が、針の長さより小さいならtrue
		if (sqrtf((m_posX + m_posY)) < needle_length)
		{
			return true;
		}
		//プレイヤーの位置が、針の長さより大きい（針から落ちている）ならfalse
		return false;

	}
	//針の座標上に居なかったらfalse
	return false;
}



//∞------------------------------------------------------------------∞
//∞*func：走るモーション
//∞*arg：なし
//∞*return：なし
//∞*heed：組み立て時に、if文で針の情報取得＆針の有無を確認すること
//∞------------------------------------------------------------------∞

void Player::run()
{
	//キーボードの情報取得
	if (g_keyTracker->pressed.Left)
	{
		m_spdX--;
	}
	if (g_keyTracker->pressed.Right)
	{
		m_spdX++;
	}

	//スペースキーでジャンプ処理
	if (g_keyTracker->pressed.Space)
	{
		if (!jump_flug)
		{
			jump_flug = true;
			m_y_prev = m_posY;		//現在のyの座標を保存
			m_posY = m_posY - 20;

		}

	}
	//ジャンプ処理
	if (jump_flug)
	{
		m_y_temp = m_posY;			//現在のy座標を保存
		m_posY += (m_posY - m_y_prev) + 1;	
		m_y_prev = m_y_temp;

		//地面に着いたらジャンプをやめる
		//※300は仮値。本来はExistence関数で針の座標上か判定をする
		//デバック用
		if (m_posY >= 300)
		{
			jump_flug = false;
		}
		//本来使用したい方
		//if (Player::Existence())
		//{
		//	jump_flug = false;
		//}
	}

	if (g_keyTracker->released.Left || g_keyTracker->released.Right)
	{
		m_spdX = 0.0f;
	}

}


//∞------------------------------------------------------------------∞
//∞*func：描画関数
//∞*arg：なし
//∞*return：なし
//∞*heed：なし
//∞------------------------------------------------------------------∞

void Player::Render()
{
	//描画
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定

	//ノーマル時
	m_spriteBatch->Draw(m_orion_normal_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();

}







