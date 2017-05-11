//**********************************//
//*	GameTitle.h
//*	タイトルシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"

class GameTitle :public GameBase
{
public:
	GameTitle();	//	コンストラクタ
	~GameTitle();	//	デストラクタ
	int UpdateGame();	//	データの更新
	wchar_t* RenderGame();//	描画する
};
