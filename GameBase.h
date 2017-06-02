//**********************************//
//*	名　前：GameBase.h
//*	内　容：基本クラスのヘッダファイル
//*	日　付：2017.04.25
//* 更新日：2017.06.02
//*	制作者：N.Shibayama & Ayaka.Y
//**********************************//

#pragma once

class GameBase
{
protected:
	int m_TimeCnt = 0;
	int m_NextScene = 0;

public:

	virtual ~GameBase() {}
	virtual int UpdateGame() = 0;
	virtual void RenderGame() = 0;
	int m_scene = 0;

};
