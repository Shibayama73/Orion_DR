//**********************************//
//*	GamePlay.h
//*	プレイシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"
#include "GameMain.h"

class GamePlay :public GameBase
{
public:
	GamePlay();	//	コンストラクタ
	~GamePlay();	//	デストラクタ
	int UpdateGame();	//	データの更新
	wchar_t* RenderGame();//	描画する

};
