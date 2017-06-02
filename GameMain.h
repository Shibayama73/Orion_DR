//***********************************//
//*	名　前：GameMain.h
//*	内　容：シーン管理
//*	日　付：2017.04.27
//* 更新日：2017.06.02
//*	制作者：N.Shibayama & Ayaka.Y
//***********************************//

#pragma once
#include "GameBase.h"
#include "GameLogo.h"
#include "GameTitle.h"
#include "GamePlay.h"
#include "GameClear.h"
#include "GameOver.h"

enum Scene
{
	LOGO,
	TITLE,
	PLAY,
	CLEAR,
	OVER
};

class GameMain
{
public:
	GameMain();
	~GameMain();
	void Scene();
	void Output();
	GameBase* m_base;

};

