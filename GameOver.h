//**********************************//
//*	GameOver.h
//*	�I�[�o�[�V�[��
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"
#include "GameMain.h"

class GameOver :public GameBase
{
public:
	GameOver();	//	�R���X�g���N�^
	~GameOver();	//	�f�X�g���N�^
	int UpdateGame();	//	�f�[�^�̍X�V
	void RenderGame();//	�`�悷��
};
