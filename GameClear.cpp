//**********************************//
//*	GameClear.cpp
//*	クリアシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GameClear.h"
#include "GameMain.h"
#include <d3d11.h>
#include "DirectXTK.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

GameClear::GameClear()
{
	m_TimeCnt = 0;
}

GameClear::~GameClear()
{

}

int GameClear::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = CLEAR;
	m_scene = CLEAR;

	if (m_TimeCnt > 120)
	{
		m_NextScene = TITLE;
	}
	return m_NextScene;
}

wchar_t * GameClear::RenderGame()
{
	wchar_t* output = L"CLEAR";
	return output;
}

