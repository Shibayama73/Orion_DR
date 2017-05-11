//**********************************//
//*	GameMain.cpp
//*	ƒV[ƒ“ŠÇ—
//*	2017.4.27
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "pch.h"
#include "GameMain.h"


GameMain::GameMain()
{
	m_base = new GameLogo();
}


GameMain::~GameMain()
{
}

void GameMain::Scene()
{
	int next_scene;
	next_scene = m_base->UpdateGame();
	if (m_base->m_scene != next_scene)
	{

		switch (next_scene)
		{
		case LOGO:
			m_base = new GameLogo();
			break;
		case TITLE:
			m_base = new GameTitle();
			break;
		case PLAY:
			m_base = new GamePlay();
			break;
		case CLEAR:
			m_base = new GameClear();
			break;
		case OVER:
			m_base = new GameOver();
			break;
		}
	}
}

wchar_t * GameMain::Output()
{
	wchar_t* output;
	output = m_base->RenderGame();
	return output;
}
