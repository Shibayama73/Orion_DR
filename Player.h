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


//キャラの幅、高さ
const int GRP_WIDTH = 96;
const int GRP_HEIGHT = 96;

enum
{
	NORMAL,		//通常
	UP,			//上昇
	DOWN,		//下降
	DIE,		//死亡
};

class Player :public ObjectBase
{
public:
	Player();
	~Player();

	//*針情報を取得する関数
	void Needle(DirectX::SimpleMath::Vector2 needle);

	//*今乗っている針の長さを取得する関数
	bool Length(bool length);

	//*針の有無を取得する関数
	bool Existence(bool length);

	//*走る関数
	void run();

	//*posYを取得する関数
	float Pos_y();

	//*Render関数
	void Render();

private:
	float a;	//y=ax+bのa（傾き）
	bool jump_flug;		//ジャンプフラグ

	int m_y_prev;		//ジャンプ用。キャラのｙ座標を保存
	int m_y_temp;		//ジャンプ用。キャラのｙ座標を保存

	Wire* wire;			//ワイヤー

	//描画
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_orion_normal_tex;	//通常時テクスチャ


};

