//**********************************//
//*	名　前：GamePlay.h
//*	内　容：プレイシーン
//*	日　付：2017.04.25
//* 更新日：2017.06.02
//*	制作者：N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

#include "Clock.h"
#include "Player.h"
#include "Wire.h"
#include "Fragment.h"
#include "Gauge.h"
#include "Time.h"
#include "Screw.h"
#include "Effect.h"

#include "ADX2Le.h"

const int FRAGMENT_MAX = 20;

class GamePlay :public GameBase
{
public:
	GamePlay();			//	コンストラクタ
	~GamePlay();		//	デストラクタ
	int UpdateGame();	//	データの更新
	void RenderGame();	//	描画する

	//ファイル読み書き
	int FileIO(int io, int score);


private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//テクスチャ

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	Clock* m_clock;		//時計
	Player* m_player;	//プレイヤー
	Wire* m_player_wire[WIRE_NUM];		//ワイヤー（プレイヤーの所持しているワイヤーを一時的に保管する）
	Fragment* m_fragment[FRAGMENT_MAX];	//欠片
	Effect* m_effect[FRAGMENT_MAX];
	Gauge* m_gauge;		//ゲージ
	Time* m_time;			//時間
	Screw* m_screw;		//ネジ

	int m_time_flag;		//時刻加算用変数
	int m_effect_time;
};
