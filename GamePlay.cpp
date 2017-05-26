//**********************************//
//*	GamePlay.cpp
//*	プレイシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GamePlay.h"
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

GamePlay::GamePlay()
{
	//m_TimeCnt = 0;

	//時間の生成
	m_time = new Time();
	//	時計生成
	m_clock = new Clock();

	//プレイヤーの生成
	m_player = new Player();

	//欠片の生成
	for (int i = 0; i < FRAGMENT_MAX; i++)
	{
		m_fragment[i] = new Fragment();
	}

	//	ゲージの生成
	m_gauge = new Gauge();


	////	描画読み込み============================================================================
	//m_deviceResources = Game::m_deviceResources.get();
	//m_spriteBatch = Game::m_spriteBatch.get();

	//ComPtr<ID3D11Resource> resource;
	//DX::ThrowIfFailed(
	//	CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/clock.png",
	//		resource.GetAddressOf(),
	//		m_texture.ReleaseAndGetAddressOf()));

	////	リソースから背景のテクスチャと判断
	//ComPtr<ID3D11Texture2D> clock;
	//DX::ThrowIfFailed(resource.As(&clock));

	////	テクスチャ情報
	//CD3D11_TEXTURE2D_DESC clockDesc;
	//clock->GetDesc(&clockDesc);

	////	テクスチャ原点を画像の中心にする
	//m_origin.x = float(clockDesc.Width / 2.0f);
	//m_origin.y = float(clockDesc.Height / 2.0f);

	////	表示座標を画面中央に指定
	//m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	//m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	////==========================================================================================

}

GamePlay::~GamePlay()
{
	//	時計破棄
	delete m_clock;

	//プレイヤーの破棄
	delete m_player;

	//欠片の破棄
	for (int i = 0; i < FRAGMENT_MAX; i++)
	{
		delete m_fragment[i];
	}

	//	ゲージの破棄
	delete m_gauge;

	//時計の破棄
	delete m_time;

}

int GamePlay::UpdateGame()
{
	m_NextScene = PLAY;
	m_scene = PLAY;

	//	各クラスの更新
	//	時計の更新
	m_clock->Update();
	m_time->CurrentTime();

	if (m_clock->getLongTipPos().x == 450 && m_clock->getLongTipPos().y == 0)
	{
		delete m_player;
	}
	//m_player->Needle(m_clock->getLongTipPos(), m_clock->getLongTipOrigin());
	//	プレイヤーの移動処理
	m_player->run(m_clock->getLongTipPos(), m_clock->getOrigin());

	//	プレイヤーの更新
	m_player->Update();

	//プレイヤーの所持しているワイヤーの保管
	for (int i = 0; i < WIRE_NUM; i++)
	{
		m_player_wire[i] = m_player->GetWire(i);
	}

	//欠片の更新
	for (int i = 0; i < FRAGMENT_MAX; i++)
	{
		m_fragment[i]->Update(m_clock->getOrigin());

		//	欠片が掴まれた状態のとき
		if (m_fragment[i]->State() == FRAGMENT_CATCH)
		{
			//	原点、長針、欠片の座標から角度を算出する
			float longTipAngle = m_clock->calAngle(m_clock->getOrigin(), m_clock->getLongTipPos(), Vector2(m_fragment[i]->GetPosX(), m_fragment[i]->GetPosY()));
			//	原点、短針、欠片の座標から角度を算出する
			float shortTipAngle = m_clock->calAngle(m_clock->getOrigin(), m_clock->getShortTipPos(), Vector2(m_fragment[i]->GetPosX(), m_fragment[i]->GetPosY()));

			//	長針と欠片の角度が一致したとき
			if (longTipAngle == 0.0f)
			{
				//	欠片が長針と同じ方向に移動する
				float fragment_angle = XMConvertToDegrees(m_clock->calAngle(m_clock->getOrigin(), m_clock->getLongTipPos(), m_clock->getShortTipPos()));
				m_fragment[i]->AttackTip(fragment_angle);
			}
			//	短針と欠片の角度が一致したとき
			if (shortTipAngle == 0.0f)
			{
				//	欠片が短針と同じ方向に移動する
				float fragment_angle = XMConvertToDegrees(m_clock->calAngle(m_clock->getOrigin(), m_clock->getLongTipPos(), m_clock->getShortTipPos()));
				m_fragment[i]->AttackTip(fragment_angle);
			}
		}
		//欠片が失われていたら
		if (m_fragment[i]->State() == FRAGMENT_LOSS)
		{
			//破棄して新たに生成する
			delete m_fragment[i];
			m_fragment[i] = new Fragment();
		}
	}

	//ワイヤーと欠片の当たり判定（ワイヤーの処理のみで、欠片の処理は関数内で）
	for (int i = 0; i < WIRE_NUM; i++)
	{
		for (int j = 0; j < FRAGMENT_MAX; j++)
		{
			//ワイヤーと欠片、それぞれ存在しているか確認
			if (m_player_wire[i] != nullptr && m_fragment[j] != nullptr)
			{
				//ワイヤーに当たっていたら
				if (m_fragment[j]->Collision(m_player_wire[i]))
				{
					//ワイヤーを消滅させる
					m_player->Elimination(i);
				}
			}

		}
	}
	

	//残り時間が０になったら
	//if (!(m_time->RemnantTime()))
	//{
	//	m_NextScene = OVER;
	//}
	return m_NextScene;
}

void GamePlay::RenderGame()
{
	//	時計描画
	m_clock->Render();

	//欠片の描画
	for (int i = 0; i < FRAGMENT_MAX; i++)
	{
		m_fragment[i]->Render();
	}

	//プレイヤーの描画
	m_player->Render();

	//	ゲージの描画
	m_gauge->Render();

	//時間の描画
	m_time->Render();




	////	スプライトの描画========================================================================
	//CommonStates m_states(m_deviceResources->GetD3DDevice());
	//m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	//m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);

	//m_spriteBatch->End();
	////==========================================================================================

}

