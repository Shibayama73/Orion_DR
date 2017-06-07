//**********************************//
//*	���@�O�FGameMain.cpp
//*	���@�e�F�V�[���Ǘ�
//*	���@�t�F2017.04.27
//* �X�V���F2017.06.02
//*	����ҁFN.Shibayama & Ayaka.Y
//**********************************//

#include "pch.h"
#include "GameMain.h"


GameMain::GameMain()
{
	//m_base = new GameLogo();

	//	�v���C�V�[���̂݃f�o�b�O�p
	m_base = new GamePlay();
	
	//m_base = new GameOver();

	//�v���g�^�C�v�p�A�^�C�g������
	//m_base = new GameLogo();

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
