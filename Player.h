//∞----------------------------------------------------∞
//∞*ファイル名：Player.cpp								∞
//∞*内容　　　：プレイヤークラス						∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.01								∞
//∞----------------------------------------------------∞

#pragma once
#include "SimpleMath.h"
#include <Keyboard.h>


//キャラの幅、高さ
const int GRP_WIDTH = 32;
const int GRP_HEIGHT = 32;

class Player
{
public:
	Player();
	~Player();

	//*針情報を取得する関数
	void Needle(DirectX::SimpleMath::Vector2 needle);

	//*針の有無を取得する関数
	bool Existence(bool length);

	//*走る関数
	void run();

private:
	float pos_x;		//座標x
	float pos_y;		//座標y
	int grp_w;			//キャラの幅
	int grp_h;			//キャラの高さ
	float spd_x;		//x軸のスピード
	float spd_y;		//y軸のスピード
	float a;

	//キーボード
	std::unique_ptr<DirectX::Keyboard>keyboard;

};

