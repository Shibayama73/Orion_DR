//***********************************//
//*	���@�O�FGameMain.h
//*	���@�e�F�V�[���Ǘ�
//*	���@�t�F2017.04.27
//* �X�V���F2017.06.02
//*	����ҁFN.Shibayama & Ayaka.Y
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

