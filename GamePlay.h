//**********************************//
//*	GamePlay.h
//*	�v���C�V�[��
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"
#include "GameMain.h"

class GamePlay :public GameBase
{
public:
	GamePlay();	//	�R���X�g���N�^
	~GamePlay();	//	�f�X�g���N�^
	int UpdateGame();	//	�f�[�^�̍X�V
	wchar_t* RenderGame();//	�`�悷��

};
