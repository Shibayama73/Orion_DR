//**********************************//
//*	GameMain.cpp
//*	シーン管理
//*	2017.4.27
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "pch.h"
#include "GameMain.h"


GameMain::GameMain()
{
	//m_base = new GameLogo();

	//	プレイシーンのみデバッグ用
	//m_base = new GamePlay();

	//プロトタイプ用、タイトルから
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

void GameMain::Output()
{
	m_base->RenderGame();
	
}
