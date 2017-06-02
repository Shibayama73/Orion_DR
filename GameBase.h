//**********************************//
//*	���@�O�FGameBase.h
//*	���@�e�F��{�N���X�̃w�b�_�t�@�C��
//*	���@�t�F2017.04.25
//* �X�V���F2017.06.02
//*	����ҁFN.Shibayama & Ayaka.Y
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
