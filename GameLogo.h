//**********************************//
//*	GameLogo.h
//*	ロゴシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"

class GameLogo :public GameBase
{
public:
	GameLogo();	//	コンストラクタ
	~GameLogo();	//	デストラクタ
	int UpdateGame();	//	データの更新
	wchar_t* RenderGame();//	描画する
};
