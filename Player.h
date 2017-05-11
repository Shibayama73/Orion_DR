//��----------------------------------------------------��
//��*�t�@�C�����FPlayer.cpp								��
//��*���e�@�@�@�F�v���C���[�N���X						��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.01								��
//��----------------------------------------------------��

#pragma once
#include "SimpleMath.h"
#include <Keyboard.h>


//�L�����̕��A����
const int GRP_WIDTH = 32;
const int GRP_HEIGHT = 32;

class Player
{
public:
	Player();
	~Player();

	//*�j�����擾����֐�
	void Needle(DirectX::SimpleMath::Vector2 needle);

	//*�j�̗L�����擾����֐�
	bool Existence(bool length);

	//*����֐�
	void run();

private:
	float pos_x;		//���Wx
	float pos_y;		//���Wy
	int grp_w;			//�L�����̕�
	int grp_h;			//�L�����̍���
	float spd_x;		//x���̃X�s�[�h
	float spd_y;		//y���̃X�s�[�h
	float a;

	//�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>keyboard;

};

