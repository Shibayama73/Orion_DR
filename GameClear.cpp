//**********************************//
//*	GameClear.cpp
//*	クリアシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GameClear.h"
#include "GameMain.h"
#include <d3d11.h>
#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>
#include "Game.h"
#include "pch.h"

#include <WICTextureLoader.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


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

void GameClear::RenderGame()
{
	
}

