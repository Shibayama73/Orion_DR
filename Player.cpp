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
	m_posX = 300.0f;
	m_posY = 510.0f;
	m_grpW = GRP_WIDTH;
	m_grpH = GRP_HEIGHT;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_jump_flug = false;
	m_vec = RIGHT;	//初期の向きは右向き

	m_wire = new Wire();

	m_y_render = m_posY;

	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//通常時画像
	ComPtr<ID3D11Resource> normal_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_normal.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_tex.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_normal_L.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_left_tex.ReleaseAndGetAddressOf()));



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
//∞*arg：針の先端の座標（Vec2）、針の原点（Vec2)
//∞*return：なし
//∞*heed：Update関数にて常に呼び出すこと
//∞------------------------------------------------------------------∞
void Player::Needle(DirectX::SimpleMath::Vector2 needle, DirectX::SimpleMath::Vector2 tip_origin)
{
	//変化の割合aの計算（needle.y-origin.y)/(needle.x-origin.x)
	a = (needle.y - tip_origin.y) / (needle.x -tip_origin.x);
	//bの計算（origin.y=(a*origin.x)+b）
	b = ((a * tip_origin.x) - tip_origin.y) * (-1);
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

bool Player::Existence(DirectX::SimpleMath::Vector2 needle, DirectX::SimpleMath::Vector2 tip_origin)
{
	float needle_length = 0;	//針の長さ(三角関数のc2=a2+b2でいうc2の部分）

	//針の長さを指定する
	needle_length = sqrtf(((tip_origin.x - needle.x) * (tip_origin.x - needle.x)) + ((tip_origin.y - needle.y) * (tip_origin.y - needle.y)));
	//needle_length = 20;
	if (!m_jump_judge_flug)
	{
		//ジャンプ中は判定しない
		return true;
	}
	else
	{
		//プレイヤーの座標と、針の座標の当たり判定
		if ((m_posY + m_grpH) > (a * m_posX + b)) 
		{
			//プレイヤーの位置が、針の長さより小さいならtrue
			if (sqrtf((m_posX + m_posY)) < needle_length)
			{
				return true;
			}
			//プレイヤーの位置が、針の長さより大きい（針から落ちている）ならfalse
			return false;
		}
	
	}
	return false;
}



//∞------------------------------------------------------------------∞
//∞*func：走るモーション
//∞*arg：なし
//∞*return：なし
//∞*heed：組み立て時に、if文で針の情報取得＆針の有無を確認すること
//∞------------------------------------------------------------------∞

void Player::run(DirectX::SimpleMath::Vector2 needle, DirectX::SimpleMath::Vector2 tip_origin)
{
	//キーボードの情報取得
	if (g_keyTracker->pressed.Left)
	{
		if (Existence(needle, tip_origin))
		{
			m_vec = LEFT;
			m_spdX--;
		}
	}
	if (g_keyTracker->pressed.Right)
	{
		if (Existence(needle, tip_origin))
		{
			m_vec = RIGHT;
			m_spdX++;
		}
	}

	//スペースキーでジャンプ処理
	if (g_keyTracker->pressed.Space)
	{
		if (!m_jump_flug)
		{
			m_jump_flug = true;
			m_jump_judge_flug = false;
			m_y_render = m_posY;

			m_y_prev = m_posY;		//現在のyの座標を保存
			m_posY = m_posY - 20;

		}

	}
	//エンターキーでワイヤー
	if (g_keyTracker->pressed.Enter)
	{
		if (Existence(needle, tip_origin))
		{
			m_vec = RIGHT;
			m_wire->Appears();
		}

	}
	//ジャンプ処理
	if (m_jump_flug)
	{
		m_y_temp = m_posY;			//現在のy座標を保存
		m_posY += (m_posY - m_y_prev) + 1;	
		m_y_prev = m_y_temp;

		//放物線のトップまで行ったらジャッジのフラグ
		if (((m_posY - m_y_prev) + 1) > 0)
		{
			m_jump_judge_flug = true;	

		}
		//本来使用したい方
		if (m_jump_judge_flug)
		{
			if (Existence(needle, tip_origin))
			{
				m_jump_flug = false;
			}

		}

		//地面に着いたらジャンプをやめる
		//※300は仮値。本来はExistence関数で針の座標上か判定をする
		////デバック用
		//if (m_posY >= m_y_render)
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
//∞*func：PosYを取得する
//∞*arg：なし
//∞*return：PosY（float）
//∞*heed：主にワイヤーの描画更新にて
//∞------------------------------------------------------------------∞
float Player::Pos_y()
{
	return m_posY;
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

	switch (m_vec)
	{
	case LEFT:
	//ノーマル（左向き）時
		m_spriteBatch->Draw(m_orion_normal_left_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);

		break;
	case RIGHT:
	//ノーマル（右向き）時
		m_spriteBatch->Draw(m_orion_normal_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
		break;
		
	}
	m_spriteBatch->End();

	//ワイヤーの描画
	m_wire->Render(m_y_render,m_vec);
}







