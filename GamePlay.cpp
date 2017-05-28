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

//	サウンド
#include "Resouces\Music\CueSheet_0.h"

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

	//時刻加算用変数の初期化
	m_time_flag = 0;

	////	描画読み込み============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_play.jpg",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

	//	リソースから背景のテクスチャと判断
	ComPtr<ID3D11Texture2D> backgraund;
	DX::ThrowIfFailed(resource.As(&backgraund));

	//	テクスチャ情報
	CD3D11_TEXTURE2D_DESC backgraundDesc;
	backgraund->GetDesc(&backgraundDesc);

	//	テクスチャ原点を画像の中心にする
	m_origin.x = float(backgraundDesc.Width / 2.0f);
	m_origin.y = float(backgraundDesc.Height / 2.0f);

	//	表示座標を画面中央に指定
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	////==========================================================================================

	//	サウンドファイルの読み込み
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

	//	サウンド再生
	ADX2Le::Play(CRI_CUESHEET_0_PLAY);

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

	//	サウンドライブラリの終了処理
	ADX2Le::Finalize();

}

int GamePlay::UpdateGame()
{
	m_NextScene = PLAY;
	m_scene = PLAY;

	//各クラスの更新===============================================//
	//	サウンドの更新
	ADX2Le::Update();

	//	時計の更新
	m_clock->Update();

	//m_time->CurrentTime();

	//長針が12時のところに来たら、現在時刻を追加
	if (m_clock->LongAngle() == 270)
	{
		if (m_time_flag == 0)
		{
			m_time->CurrentTime();
		}
		m_time_flag++;

		if (m_time_flag > 3)
		{
			m_time_flag = 0;
		}

	}

	//m_player->Needle(m_clock->getLongTipPos(), m_clock->getLongTipOrigin());
	//	プレイヤーの移動処理
	m_player->run(m_clock->getLongTipPos(), m_clock->getOrigin());

	//	プレイヤーの更新
	m_player->Update();

	//スペースキーでワイヤー
	if (g_keyTracker->pressed.Space)
	{
		m_player->WireShot();
		//	効果音
		ADX2Le::Play(CRI_CUESHEET_0_THROW);
	}


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
		//∞-------------------------------------------------------------------------------------------------------------------∞//
		//∞針と欠片の当たり判定

			float under_angle;			//*長針と短針の間の角
			float under_angle2;			//*短針と長針の間の角
			float long_angle;			//*長針と原点の間の角度
			float short_angle;			//*短針と原点の間の角度

			float big_angle;			//*大きさ判定用。長針と短針を比べて大きい方の角度を代入
			float small_angle;			//*大きさ判定用。長針と短針を比べて小さい方の角度を代入
			float null_angle;			//*入れ替え用

			//長針と原点の間の角度を代入
			long_angle = m_clock->LongAngle();
			//短針と原点の間の角度を代入
			short_angle = m_clock->ShortAngle();

			//長針の角度-短針の角度
			under_angle = long_angle - short_angle;
			//短針の角度-長針の角度
			under_angle2 = short_angle - long_angle;

			//それぞれの間の角度が180度以上の場合、逆側の角度を求めて代入する
			if (under_angle > 180)
			{
				under_angle = (360 - long_angle) + short_angle;
			}
			if (under_angle2 > 180)
			{
				under_angle2 = (360 - short_angle) + long_angle;
			}


			//長針の角度と短針の角度を比べて、大きい方をbig、小さい方をshortに代入
			if (long_angle > short_angle)
			{
				big_angle = long_angle;
				small_angle = short_angle;
			}
			else
			{
				big_angle = short_angle;
				small_angle = long_angle;
			}

			//大きい方の角が301度以上で、更に小さい方の角が60度未満の場合、小さい方の角に360足して、大きい方と小さい方を入れ替える
			//※原点との間の角が0～60の時に欠片を挟むことが出来なくなるバグ防止のため
			if (big_angle > 301 && small_angle < 60)
			{
				small_angle += 360;
				null_angle = big_angle;
				big_angle = small_angle;
				small_angle = big_angle;
			}

			//長針と短針の間の角が60度以下の場合のみ判定
			if (under_angle > 0 && under_angle < 60)
			{
				//小さい方の針の角度よりも欠片の角度が大きい、かつ大きい針の角度よりも欠片の角度が小さい場合
				if ((small_angle < m_fragment[i]->Angle(m_clock->getOrigin())) && (big_angle > m_fragment[i]->Angle(m_clock->getOrigin())))
				{
					//	欠片が消失する
					m_fragment[i]->AttackTip();
					//	効果音
					ADX2Le::Play(CRI_CUESHEET_0_VANISH);
					//	ゲージがカウントされる
					m_gauge->addGradation(m_fragment[i]->State());

				}
			}
			//短針と長針の間の角が60度以下の場合のみ判定
			if (under_angle2 > 0 && under_angle2 < 60)
			{
				//小さい方の針の角度よりも欠片の角度が大きい、かつ大きい針の角度よりも欠片の角度が小さい場合
				if ((big_angle > m_fragment[i]->Angle(m_clock->getOrigin())) && (small_angle < m_fragment[i]->Angle(m_clock->getOrigin())))
				{
					//	欠片が消失する
					m_fragment[i]->AttackTip();
					//	効果音
					ADX2Le::Play(CRI_CUESHEET_0_VANISH);
					//	ゲージがカウントされる
					m_gauge->addGradation(m_fragment[i]->State());

				}
			}
		//∞-------------------------------------------------------------------------------------------------------------------∞//
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

					//	効果音
					ADX2Le::Play(CRI_CUESHEET_0_HIT);
				}
			}

		}
	}


	//残り時間が０になったら
	if (!(m_time->RemnantTime()))
	{
		FileIO(1, m_gauge->getGradation());
		m_NextScene = OVER;
	}
	return m_NextScene;
}

void GamePlay::RenderGame()
{
	////	スプライトの描画========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();
	////==========================================================================================
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


}

//∞------------------------------------------------------------------∞
//∞*func：ファイル読み書き関数
//∞*arg：読み書き指定（０：読み込み、１：書き込み）、読み書きしたい変数
//∞*return：正常（０）、エラー（１）
//∞------------------------------------------------------------------∞
int GamePlay::FileIO(int io, int score)
{
	char *Filename = "data.txt";
	FILE *fp;

	if (io == 0)
	{
		//読み込み
		fp = fopen(Filename, "r");
		if (fp == NULL)
		{
			return 1;
		}
		fscanf(fp, "%d", &score);
	}
	else
	{
		//書き込み
		fp = fopen(Filename, "w");
		if (fp == NULL)
		{
			return 1;
		}
		fprintf(fp, "%d", score);
	}
	fclose(fp);
	return 0;
}

