//**********************************//
//*	GameLogo.h
//*	���S�V�[��
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"

class GameLogo :public GameBase
{
public:
	GameLogo();	//	�R���X�g���N�^
	~GameLogo();	//	�f�X�g���N�^
	int UpdateGame();	//	�f�[�^�̍X�V
	void RenderGame();//	�`�悷��
};
