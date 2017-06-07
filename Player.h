//∞----------------------------------------------------∞
//∞*ファイル名：Player.cpp								∞
//∞*内容　　　：プレイヤークラス						∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.01								∞
//∞----------------------------------------------------∞

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

#include "Wire.h"


//キャラの数値
const int GRP_WIDTH = 128;
const int GRP_HEIGHT = 128;

enum STATE
{
	NORMAL,		//通常
	DIE,		//死亡
	DAMAGE,		//ダメージ
};

enum VEC
{
	LEFT,
	RIGHT,
};

enum ANIMATEION
{
	UP,
	DOWN,
};

//プレイヤーが所持している一度に出せるワイヤーの数
const int WIRE_NUM = 3;

class Player :public ObjectBase
{
public:
	Player();
	~Player();

	//*走る関数
	void run();

	//*更新関数
	void Update();
	//*Render関数
	void Render();

	//*ワイヤーの情報を取得
	Wire* GetWire(int i);

	//*ワイヤーを発射させる関数
	void WireShot();

	//*ワイヤーを消滅させる関数
	void Elimination(int i);

	//*プレイヤーの状態をダメージ状態にする
	void Damage();


	int State();		//状態の取得


private:
	//時計の一次関数を求めるための変数
	float a;	//y=ax+bのa（傾き）
	float b;	

	bool m_vec;		//向き（０：左、１：右）

	bool m_jump_flug;		//ジャンプフラグ
	bool m_jump_judge_flug;
	bool m_animetion;	//0がUP、1がDOWN
	int time_cnt;

	float m_y_prev;		//ジャンプ用。キャラのｙ座標を保存
	float m_y_temp;		//ジャンプ用。キャラのｙ座標を保存
	float m_y_render;		//ワイヤーのRender用

	Wire* m_wire[WIRE_NUM];			//ワイヤー

	float m_wire_posX[WIRE_NUM];		//ワイヤーの位置を取得

	int m_player_revival;				//スタン状態からの回復に使用する変数



	//描画
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_orion_normal_tex;	//通常時テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_orion_normal_left_tex;	//通常時左向きテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_orion_damage_tex;	//ダメージ時テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_orion_damage_left_tex;	//ダメージ時テクスチャ


};

