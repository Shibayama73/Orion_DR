//��----------------------------------------------------��
//��*�t�@�C�����FPlayer.cpp								��
//��*���e�@�@�@�F�v���C���[�N���X						��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.01								��
//��----------------------------------------------------��

#include "pch.h"
#include "Player.h"

using namespace DirectX;

Player::Player()
{
	//�ϐ��̏������i�l�͂��ꂼ�ꉼ�l�j
	pos_x = 0.0f;
	pos_y = 0.0f;
	grp_w = GRP_WIDTH;
	grp_h = GRP_HEIGHT;
	spd_x = 0.0f;
	spd_y = 0.0f;

	//�L�[�{�[�h�̏�����
	keyboard = std::make_unique<Keyboard>();


}


Player::~Player()
{
}


//��------------------------------------------------------------------��
//��*func�F�j�̏����擾����
//��*arg�F�j�̐�[�̍��W�iVec2�j
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Player::Needle(DirectX::SimpleMath::Vector2 needle)
{
	//�ꎟ�֐��̌X���̎w��
	//y=ax+b(���_�͌Œ�Ȃ̂ŁAb�͕ϓ����Ȃ�(���l�͂O�j�j
	a = (needle.y - 0) / needle.x;
}



//��------------------------------------------------------------------��
//��*func�F�j�̗L�����m�F����
//��*arg�F���j���Z�j���i���j�Ftrue�A�Z�j�Ffalse�j
//��*return�F�j�����邩�A�Ȃ����i����Ftrue�A�Ȃ��Ffalse�j
//��------------------------------------------------------------------��

bool Player::Existence(bool length)
{
	float needle_length = 0;	//�j�̒���(�O�p�֐���c2=a2+b2�ł���c2�̕����j

	switch (length)
	{
		//���j�̏ꍇ
	case true:
		//�j�̒������w�肷��
		needle_length = 20;
		break;
		//�Z�j�̏ꍇ
	case false:
		//�j�̒������w�肷��
		needle_length = 10;
		break;
	}

	//�v���C���[�̍��W�ƁA�j�̍��W�̓����蔻��
	if ((pos_y > (a * pos_x + 0)) || (pos_y > (a * (pos_x + grp_w) + 0))
		|| (pos_y + grp_h > (a * pos_x + 0)) || (pos_y + grp_h > (a * (pos_x + grp_w) + 0)))
	{
		//�v���C���[�̈ʒu���A�j�̒�����菬�����Ȃ�true
		if (sqrtf((pos_x + pos_y)) < needle_length)
		{
			return true;
		}
		//�v���C���[�̈ʒu���A�j�̒������傫���i�j���痎���Ă���j�Ȃ�false
		return false;

	}
	//�j�̍��W��ɋ��Ȃ�������false
	return false;
}



//��------------------------------------------------------------------��
//��*func�F���郂�[�V����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*heed�F�g�ݗ��Ď��ɁAif���Őj�̏��擾���j�̗L�����m�F���邱��
//��------------------------------------------------------------------��

void Player::run()
{
	//�L�[�{�[�h�̏��擾
	Keyboard::State key = keyboard->GetState();

	if (key.Left)
	{
		pos_x++;
	}
	if (key.Right)
	{
		pos_x--;
	}

}


