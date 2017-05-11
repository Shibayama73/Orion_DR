//**********************************//
//*	GamePlay.cpp
//*	プレイシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GamePlay.h"
#include "GameMain.h"
#include <d3d11.h>

#include "DirectXTK.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

GamePlay::GamePlay()
{
	m_TimeCnt = 0;

}

GamePlay::~GamePlay()
{

}

int GamePlay::UpdateGame()
{
	m_NextScene = PLAY;
	m_scene = PLAY;
	
	m_TimeCnt++;
	if (m_TimeCnt > 120)
	{
		m_NextScene = CLEAR;
	}

	return m_NextScene;
}

wchar_t * GamePlay::RenderGame()
{
	wchar_t* output = L"Play";
	return output;
}
