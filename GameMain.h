//***********************************//
//*	GameMain.h
//*	ÉVÅ[Éìä«óù
//*	2017.4.27
//*	N.Shibayama & Ayaka.Y
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

