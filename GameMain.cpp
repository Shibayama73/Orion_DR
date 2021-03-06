//**********************************//
//*	名　前：GameMain.cpp
//*	内　容：シーン管理
//*	日　付：2017.04.27
//* 更新日：2017.06.02
//*	制作者：N.Shibayama & Ayaka.Y
//**********************************//

#include "pch.h"
#include "GameMain.h"


GameMain::GameMain()
{
	//	プレイシーンのみデバッグ用
	//m_base = new GamePlay();
	
	//プロトタイプ用、ロゴシーンから
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
		case RANKING:
			m_base = new GameRanking();
			break;
		case STORY:
			m_base = new GameStory();
			break;
		}
	}
}

void GameMain::Output()
{
	m_base->RenderGame();
	
}
