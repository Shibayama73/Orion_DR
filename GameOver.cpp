//**********************************//
//*	GameOver.cpp
//*	オーバーシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GameOver.h"
#include <d3d11.h>

#include "DirectXTK.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;


GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

int GameOver::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = OVER;
	m_scene = OVER;
	if (m_TimeCnt > 120)
	{
		m_NextScene = TITLE;
	}

	return m_NextScene;
}

wchar_t * GameOver::RenderGame()
{
	wchar_t* output = L"Over";
	return output;
}
