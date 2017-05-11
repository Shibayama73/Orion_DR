//**********************************//
//*	GameTitle.cpp
//*	タイトルシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GameTitle.h"
#include "GameMain.h"
#include <d3d11.h>

#include "DirectXTK.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

GameTitle::GameTitle()
{
	m_TimeCnt = 0;
}

GameTitle::~GameTitle()
{

}

int GameTitle::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = TITLE;
	m_scene = TITLE;

	if (m_TimeCnt > 120)
	{
		m_NextScene = PLAY;
	}

	return m_NextScene;
}

wchar_t * GameTitle::RenderGame()
{
	wchar_t* output = L"Title";
	return output;
}

