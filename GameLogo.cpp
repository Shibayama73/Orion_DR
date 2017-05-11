//**********************************//
//*	GameLogo.cpp
//*	ÉçÉSÉVÅ[Éì
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GameLogo.h"
#include "GameMain.h"
#include <d3d11.h>

#include "DirectXTK.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

GameLogo::GameLogo()
{
	m_TimeCnt = 0;
}

GameLogo::~GameLogo()
{

}

int GameLogo::UpdateGame()
{
	m_TimeCnt++;
	m_NextScene = LOGO;
	m_scene = LOGO;

	if (m_TimeCnt > 120)
	{
		m_NextScene = TITLE;
	}
	return m_NextScene;

}

wchar_t* GameLogo::RenderGame()
{
	wchar_t* output = L"LOGO";

	return output;

}
