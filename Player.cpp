//��----------------------------------------------------��
//��*�t�@�C�����FPlayer.cpp								��
//��*���e�@�@�@�F�v���C���[�N���X						��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.01								��
//��----------------------------------------------------��

#include "pch.h"
#include "Player.h"

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


//��------------------------------------------------------------------��
//��*func�F�R���X�g���N�^
//��*arg�F�Ȃ�
//��------------------------------------------------------------------��

Player::Player()
{
	//�ϐ��̏������i�l�͂��ꂼ�ꉼ�l�j
	m_posX = 10.0f;
	m_posY = 300.0f;
	m_grpW = GRP_WIDTH;
	m_grpH = GRP_HEIGHT;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	jump_flug = false;

	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�ʏ펞�摜
	ComPtr<ID3D11Resource> normal_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_normal.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_tex.ReleaseAndGetAddressOf()));


	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> orion;
	DX::ThrowIfFailed(normal_resource.As(&orion));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC orionDesc;
	orion->GetDesc(&orionDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(orionDesc.Width / 2.0f);
	m_origin.y = float(orionDesc.Height / 2.0f);


}

//��------------------------------------------------------------------��
//��*func�F�f�X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��

Player::~Player()
{
}


//��------------------------------------------------------------------��
//��*func�F�j�̏����擾����
//��*arg�F�j�̐�[�̍��W�iVec2�j
//��*return�F�Ȃ�
//��*heed�FUpdate�֐��ɂď�ɌĂяo������
//��------------------------------------------------------------------��
void Player::Needle(DirectX::SimpleMath::Vector2 needle)
{
	//�ꎟ�֐��̌X���̎w��
	//y=ax+b(���_�͌Œ�Ȃ̂ŁAb�͕ϓ����Ȃ�(���l�͂O�j�j
	a = (needle.y - 0) / needle.x;
}

//��------------------------------------------------------------------��
//��*func�F������Ă���j�̒������擾����
//��*arg�Fclock�֐����璷�j���Z�j���i���j�Ftrue�A�Z�j�Ffalse�j
//��*return�F���j���Z�j���i���j�Ftrue�A�Z�j�Ffalse�j
//��*heed�FUpdate�֐��ɂď�ɌĂяo������
//��------------------------------------------------------------------��

bool Player::Length(bool length)
{

	return false;
}



//��------------------------------------------------------------------��
//��*func�F�j�̗L�����m�F����
//��*arg�F���j���Z�j���i���j�Ftrue�A�Z�j�Ffalse�j
//��*return�F�j�����邩�A�Ȃ����i����Ftrue�A�Ȃ��Ffalse�j
//��*heed�F�����́ALength()���g���BUpdate�ŏ�ɌĂяo��
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
	if ((m_posY > (a * m_posX + 0)) || (m_posY > (a * (m_posX + m_grpW) + 0))
		|| (m_posY + m_grpH > (a * m_posX + 0)) || (m_posY + m_grpH > (a * (m_posX + m_grpW) + 0)))
	{
		//�v���C���[�̈ʒu���A�j�̒�����菬�����Ȃ�true
		if (sqrtf((m_posX + m_posY)) < needle_length)
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
	if (g_keyTracker->pressed.Left)
	{
		m_spdX--;
	}
	if (g_keyTracker->pressed.Right)
	{
		m_spdX++;
	}

	//�X�y�[�X�L�[�ŃW�����v����
	if (g_keyTracker->pressed.Space)
	{
		if (!jump_flug)
		{
			jump_flug = true;
			m_y_prev = m_posY;		//���݂�y�̍��W��ۑ�
			m_posY = m_posY - 20;

		}

	}
	//�W�����v����
	if (jump_flug)
	{
		m_y_temp = m_posY;			//���݂�y���W��ۑ�
		m_posY += (m_posY - m_y_prev) + 1;	
		m_y_prev = m_y_temp;

		//�n�ʂɒ�������W�����v����߂�
		//��300�͉��l�B�{����Existence�֐��Őj�̍��W�ォ���������
		//�f�o�b�N�p
		if (m_posY >= 300)
		{
			jump_flug = false;
		}
		//�{���g�p��������
		//if (Player::Existence())
		//{
		//	jump_flug = false;
		//}
	}

	if (g_keyTracker->released.Left || g_keyTracker->released.Right)
	{
		m_spdX = 0.0f;
	}

}


//��------------------------------------------------------------------��
//��*func�F�`��֐�
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*heed�F�Ȃ�
//��------------------------------------------------------------------��

void Player::Render()
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	//�m�[�}����
	m_spriteBatch->Draw(m_orion_normal_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();

}







