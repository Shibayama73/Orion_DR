//**********************************//
//*	���@�O�FClock.h
//*	���@�e�F���v�N���X
//*	���@�t�F2017.5.2
//*	����ҁFN.Shibayama
//**********************************//

#pragma once
#include "Game.h"
#include "SimpleMath.h"
#include "ObjectBase.h"

class Clock :public ObjectBase
{
protected:
	bool m_hand;									//���v�̐j(���j(true)�A�Z�j(false))
	DirectX::SimpleMath::Vector2 m_longTipPos;		//���j�̐�[���W
	DirectX::SimpleMath::Vector2 m_shotTipPos;		//�Z�j�̐�[���W

public:
	Clock();
	~Clock();
	void Update();									//�X�V
	void Render();									//�`��
	bool getHand();									//�j�̏�Ԏ擾
	DirectX::SimpleMath::Vector2 getLongTipPos();	//�j�̐�[���W�擾
	DirectX::SimpleMath::Vector2 getShotTipPos();	//�j�̐�[���W�擾
	void clockwise();								//�j���E���ɓ�����


};