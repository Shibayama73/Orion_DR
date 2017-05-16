//**********************************//
//*	GameBase.h
//*	��{�N���X�̃w�b�_�t�@�C��
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
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
