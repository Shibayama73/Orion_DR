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
using namespace std;


//∞------------------------------------------------------------------∞
//∞*func：コンストラクタ
//∞*arg：なし
//∞------------------------------------------------------------------∞

Player::Player()
{
	//変数の初期化（値はそれぞれ仮値）
	//m_posX = 300.0f;
	//m_posY = 640.0f;

	m_posX = 450.0f;
	m_posY = 600.0f;
	//m_posX = 450.0f;
	//m_posY = 0.0f;

	m_grpW = GRP_WIDTH;
	m_grpH = GRP_HEIGHT;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	//m_jump_flug = false;
	m_vec = RIGHT;	//初期の向きは右向き
	m_animetion = UP;
	time_cnt = 0;
	//m_wire = new Wire();

	m_state = NORMAL;
	for (int i = 0; i < WIRE_NUM; i++)
	{
		m_wire[i] = nullptr;
	}

	//描画用
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//通常時画像
	ComPtr<ID3D11Resource> normal_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_1.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_tex.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_L_1.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_left_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_down.png",
			normal_resource.GetAddressOf(),
			m_orion_damage_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_down_L.png",
			normal_resource.GetAddressOf(),
			m_orion_damage_left_tex.ReleaseAndGetAddressOf()));


	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> orion;
	DX::ThrowIfFailed(normal_resource.As(&orion));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC orionDesc;
	orion->GetDesc(&orionDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(orionDesc.Width / 2.0f);
	m_origin.y = float(orionDesc.Height / 2.0f);

	m_player_revival = 0;


}

//∞------------------------------------------------------------------∞
//∞*func：デストラクタ
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞

Player::~Player()
{
	//ワイヤーの破棄
	for (int i = 0; i < WIRE_NUM; i++)
	{
		delete m_wire[i];
	}
}


//∞------------------------------------------------------------------∞
//∞*func：走るモーション
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞

void Player::run()
{
	//キーボードの情報取得
	if (g_keyTracker->pressed.Left)
	{
		m_vec = LEFT;
		m_spdX = -3;
	}
	if (g_keyTracker->pressed.Right)
	{
		m_vec = RIGHT;
		m_spdX = 3;
	}
	//キーを放したらspdをもとに戻す
	if (g_keyTracker->released.Left)
	{
		m_spdX = 0.0f;
	}
	if (g_keyTracker->released.Right)
	{
		m_spdX = 0.0f;
	}




	//左の壁の判定
	if (m_posX - (GRP_WIDTH / 2) < 180)
	{
		m_posX = 180 + (GRP_WIDTH / 2);
		m_spdX = 0;
	}
	//右の壁の判定
	if (m_posX + (GRP_WIDTH / 2) > 750)
	{
		m_posX = 750 - (GRP_WIDTH / 2);
		m_spdX = 0;
	}



}

//∞------------------------------------------------------------------∞
//∞*func：更新関数
//∞*arg：なし
//∞*return：なし
//∞*heed：なし
//∞------------------------------------------------------------------∞

void Player::Update()
{
	time_cnt++;
	//アニメーション用（上下）
	if (time_cnt > 120)
	{
		m_spdY = 0.0f;
		switch (m_animetion)
		{
		case UP:
			m_spdY -= 0.1;
			m_animetion = DOWN;
			break;
		case DOWN:
			m_spdY += 0.1;
			m_animetion = UP;
			break;
		}
		time_cnt = 0;
	}

	//もしダメージ状態なら
	if (m_state == DAMAGE)
	{
		m_spdX = 0;
		m_spdY = 0;
		//通常状態に戻るまでのカウント
		m_player_revival++;
	}

	//カウントが１２０フレーム超えたら、状態をノーマルに戻す
	if (m_player_revival > 180)
	{
		m_state = NORMAL;
		//通常状態に戻るまでのカウントを初期化
		m_player_revival = 0;
	}

	m_posX += m_spdX;
	m_posY += m_spdY;

	//ワイヤーの更新
	for (int i = 0; i < WIRE_NUM; i++)
	{
		if (m_wire[i] != nullptr)
		{
			m_wire[i]->Update(m_wire_posX[i]);
			//場外に出ていたら、deleteして、nullptrを入れる
			if (m_wire[i]->State() == false)
			{
				delete m_wire[i];
				m_wire[i] = nullptr;
			}
		}
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

	if (m_state == NORMAL)
	{
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
	}
	//ダメージを食らっているとき
	else if (m_state == DAMAGE)
	{
		switch (m_vec)
		{
		case LEFT:
			//ノーマル（左向き）時
			m_spriteBatch->Draw(m_orion_damage_left_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);

			break;
		case RIGHT:
			//ノーマル（右向き）時
			m_spriteBatch->Draw(m_orion_damage_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
			break;

		}
	}
	m_spriteBatch->End();

	//ワイヤーの描画
	for (int i = 0; i < WIRE_NUM; i++)
	{
		if (m_wire[i] != nullptr)
		{
			m_wire[i]->Render(m_wire_posX[i]);
		}
	}
}

//∞------------------------------------------------------------------∞
//∞*func：ワイヤーを取得（m_wire[i]）
//∞*arg：何個目か（i）
//∞*return：ワイヤー。nullptrならnullptrを返す
//∞*heed：GamePlayで使用
//∞------------------------------------------------------------------∞
Wire * Player::GetWire(int i)
{
	if (m_wire[i] != nullptr)
	{
		return m_wire[i];
	}

	return nullptr;
}

//∞------------------------------------------------------------------∞
//∞*func：ワイヤーを発射する
//∞*arg：なし
//∞*return：なし
//∞*heed：スペースキーが押されたら呼び出し
//∞------------------------------------------------------------------∞
void Player::WireShot()
{
	for (int i = 0; i < WIRE_NUM; i++)
	{
		//ワイヤーが作られてなかったら
		if (m_wire[i] == nullptr)
		{
			m_wire[i] = new Wire(m_posX);
			m_wire_posX[i] = m_posX;
			break;
		}
	}

}

//∞------------------------------------------------------------------∞
//∞*func：ワイヤーを消滅させる関数
//∞*arg：何個目のワイヤーか(i）
//∞*return：なし
//∞*heed：欠片をキャッチしたらGamePlayで呼び出す
//∞------------------------------------------------------------------∞
void Player::Elimination(int i)
{
	m_wire[i]->Elimination();
}

//∞------------------------------------------------------------------∞
//∞*func：ダメージ状態にする
//∞*arg：なし
//∞*return：なし
//∞------------------------------------------------------------------∞
void Player::Damage()
{
	m_state = DAMAGE;
}

//∞------------------------------------------------------------------∞
//∞*func：状態を取得する
//∞*arg：なし
//∞*return：m_state
//∞------------------------------------------------------------------∞
int Player::State()
{
	return m_state;
}








