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
	m_posX = 300.0f;
	m_posY = 510.0f;
	m_grpW = GRP_WIDTH;
	m_grpH = GRP_HEIGHT;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_jump_flug = false;
	m_vec = RIGHT;	//�����̌����͉E����

	m_wire = new Wire();

	m_y_render = m_posY;

	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�ʏ펞�摜
	ComPtr<ID3D11Resource> normal_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_normal.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_tex.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_normal_L.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_left_tex.ReleaseAndGetAddressOf()));



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
//��*arg�F�j�̐�[�̍��W�iVec2�j�A�j�̌��_�iVec2)
//��*return�F�Ȃ�
//��*heed�FUpdate�֐��ɂď�ɌĂяo������
//��------------------------------------------------------------------��
void Player::Needle(DirectX::SimpleMath::Vector2 needle, DirectX::SimpleMath::Vector2 tip_origin)
{
	//�ω��̊���a�̌v�Z�ineedle.y-origin.y)/(needle.x-origin.x)
	a = (needle.y - tip_origin.y) / (needle.x -tip_origin.x);
	//b�̌v�Z�iorigin.y=(a*origin.x)+b�j
	b = ((a * tip_origin.x) - tip_origin.y) * (-1);
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

bool Player::Existence(DirectX::SimpleMath::Vector2 needle, DirectX::SimpleMath::Vector2 tip_origin)
{
	float needle_length = 0;	//�j�̒���(�O�p�֐���c2=a2+b2�ł���c2�̕����j

	//�j�̒������w�肷��
	needle_length = sqrtf(((tip_origin.x - needle.x) * (tip_origin.x - needle.x)) + ((tip_origin.y - needle.y) * (tip_origin.y - needle.y)));
	//needle_length = 20;
	if (!m_jump_judge_flug)
	{
		//�W�����v���͔��肵�Ȃ�
		return true;
	}
	else
	{
		//�v���C���[�̍��W�ƁA�j�̍��W�̓����蔻��
		if ((m_posY + m_grpH) > (a * m_posX + b)) 
		{
			//�v���C���[�̈ʒu���A�j�̒�����菬�����Ȃ�true
			if (sqrtf((m_posX + m_posY)) < needle_length)
			{
				return true;
			}
			//�v���C���[�̈ʒu���A�j�̒������傫���i�j���痎���Ă���j�Ȃ�false
			return false;
		}
	
	}
	return false;
}



//��------------------------------------------------------------------��
//��*func�F���郂�[�V����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*heed�F�g�ݗ��Ď��ɁAif���Őj�̏��擾���j�̗L�����m�F���邱��
//��------------------------------------------------------------------��

void Player::run(DirectX::SimpleMath::Vector2 needle, DirectX::SimpleMath::Vector2 tip_origin)
{
	//�L�[�{�[�h�̏��擾
	if (g_keyTracker->pressed.Left)
	{
		if (Existence(needle, tip_origin))
		{
			m_vec = LEFT;
			m_spdX--;
		}
	}
	if (g_keyTracker->pressed.Right)
	{
		if (Existence(needle, tip_origin))
		{
			m_vec = RIGHT;
			m_spdX++;
		}
	}

	//�X�y�[�X�L�[�ŃW�����v����
	if (g_keyTracker->pressed.Space)
	{
		if (!m_jump_flug)
		{
			m_jump_flug = true;
			m_jump_judge_flug = false;
			m_y_render = m_posY;

			m_y_prev = m_posY;		//���݂�y�̍��W��ۑ�
			m_posY = m_posY - 20;

		}

	}
	//�G���^�[�L�[�Ń��C���[
	if (g_keyTracker->pressed.Enter)
	{
		if (Existence(needle, tip_origin))
		{
			m_vec = RIGHT;
			m_wire->Appears();
		}

	}
	//�W�����v����
	if (m_jump_flug)
	{
		m_y_temp = m_posY;			//���݂�y���W��ۑ�
		m_posY += (m_posY - m_y_prev) + 1;	
		m_y_prev = m_y_temp;

		//�������̃g�b�v�܂ōs������W���b�W�̃t���O
		if (((m_posY - m_y_prev) + 1) > 0)
		{
			m_jump_judge_flug = true;	

		}
		//�{���g�p��������
		if (m_jump_judge_flug)
		{
			if (Existence(needle, tip_origin))
			{
				m_jump_flug = false;
			}

		}

		//�n�ʂɒ�������W�����v����߂�
		//��300�͉��l�B�{����Existence�֐��Őj�̍��W�ォ���������
		////�f�o�b�N�p
		//if (m_posY >= m_y_render)
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
//��*func�FPosY���擾����
//��*arg�F�Ȃ�
//��*return�FPosY�ifloat�j
//��*heed�F��Ƀ��C���[�̕`��X�V�ɂ�
//��------------------------------------------------------------------��
float Player::Pos_y()
{
	return m_posY;
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

	switch (m_vec)
	{
	case LEFT:
	//�m�[�}���i�������j��
		m_spriteBatch->Draw(m_orion_normal_left_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);

		break;
	case RIGHT:
	//�m�[�}���i�E�����j��
		m_spriteBatch->Draw(m_orion_normal_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
		break;
		
	}
	m_spriteBatch->End();

	//���C���[�̕`��
	m_wire->Render(m_y_render,m_vec);
}







