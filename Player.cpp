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
using namespace std;


//��------------------------------------------------------------------��
//��*func�F�R���X�g���N�^
//��*arg�F�Ȃ�
//��------------------------------------------------------------------��

Player::Player()
{
	//�ϐ��̏������i�l�͂��ꂼ�ꉼ�l�j
	//m_posX = 300.0f;
	//m_posY = 640.0f;

	m_posX = 450.0f;
	m_posY = 600.0f;
	//m_posX = 450.0f;
	//m_posY = 0.0f;

	m_grpW = GRP_WIDTH;
	m_grpH = GRP_HEIGHT;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	//m_jump_flug = false;
	m_vec = RIGHT;	//�����̌����͉E����
	m_animetion = UP;
	time_cnt = 0;
	//m_wire = new Wire();

	m_state = NORMAL;
	for (int i = 0; i < WIRE_NUM; i++)
	{
		m_wire[i] = nullptr;
	}

	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�ʏ펞�摜
	ComPtr<ID3D11Resource> normal_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_1.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_tex.ReleaseAndGetAddressOf()));

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_L_1.png",
			normal_resource.GetAddressOf(),
			m_orion_normal_left_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_down.png",
			normal_resource.GetAddressOf(),
			m_orion_damage_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/orion_down_L.png",
			normal_resource.GetAddressOf(),
			m_orion_damage_left_tex.ReleaseAndGetAddressOf()));


	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> orion;
	DX::ThrowIfFailed(normal_resource.As(&orion));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC orionDesc;
	orion->GetDesc(&orionDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(orionDesc.Width / 2.0f);
	m_origin.y = float(orionDesc.Height / 2.0f);

	m_player_revival = 0;


}

//��------------------------------------------------------------------��
//��*func�F�f�X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��

Player::~Player()
{
	//���C���[�̔j��
	for (int i = 0; i < WIRE_NUM; i++)
	{
		delete m_wire[i];
	}
}


//��------------------------------------------------------------------��
//��*func�F���郂�[�V����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��

void Player::run()
{
	//�L�[�{�[�h�̏��擾
	if (g_keyTracker->pressed.Left)
	{
		m_vec = LEFT;
		m_spdX = -3;
	}
	if (g_keyTracker->pressed.Right)
	{
		m_vec = RIGHT;
		m_spdX = 3;
	}
	//�L�[���������spd�����Ƃɖ߂�
	if (g_keyTracker->released.Left)
	{
		m_spdX = 0.0f;
	}
	if (g_keyTracker->released.Right)
	{
		m_spdX = 0.0f;
	}




	//���̕ǂ̔���
	if (m_posX - (GRP_WIDTH / 2) < 180)
	{
		m_posX = 180 + (GRP_WIDTH / 2);
		m_spdX = 0;
	}
	//�E�̕ǂ̔���
	if (m_posX + (GRP_WIDTH / 2) > 750)
	{
		m_posX = 750 - (GRP_WIDTH / 2);
		m_spdX = 0;
	}



}

//��------------------------------------------------------------------��
//��*func�F�X�V�֐�
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*heed�F�Ȃ�
//��------------------------------------------------------------------��

void Player::Update()
{
	time_cnt++;
	//�A�j���[�V�����p�i�㉺�j
	if (time_cnt > 120)
	{
		m_spdY = 0.0f;
		switch (m_animetion)
		{
		case UP:
			m_spdY -= 0.1;
			m_animetion = DOWN;
			break;
		case DOWN:
			m_spdY += 0.1;
			m_animetion = UP;
			break;
		}
		time_cnt = 0;
	}

	//�����_���[�W��ԂȂ�
	if (m_state == DAMAGE)
	{
		m_spdX = 0;
		m_spdY = 0;
		//�ʏ��Ԃɖ߂�܂ł̃J�E���g
		m_player_revival++;
	}

	//�J�E���g���P�Q�O�t���[����������A��Ԃ��m�[�}���ɖ߂�
	if (m_player_revival > 180)
	{
		m_state = NORMAL;
		//�ʏ��Ԃɖ߂�܂ł̃J�E���g��������
		m_player_revival = 0;
	}

	m_posX += m_spdX;
	m_posY += m_spdY;

	//���C���[�̍X�V
	for (int i = 0; i < WIRE_NUM; i++)
	{
		if (m_wire[i] != nullptr)
		{
			m_wire[i]->Update(m_wire_posX[i]);
			//��O�ɏo�Ă�����Adelete���āAnullptr������
			if (m_wire[i]->State() == false)
			{
				delete m_wire[i];
				m_wire[i] = nullptr;
			}
		}
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

	if (m_state == NORMAL)
	{
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
	}
	//�_���[�W��H����Ă���Ƃ�
	else if (m_state == DAMAGE)
	{
		switch (m_vec)
		{
		case LEFT:
			//�m�[�}���i�������j��
			m_spriteBatch->Draw(m_orion_damage_left_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);

			break;
		case RIGHT:
			//�m�[�}���i�E�����j��
			m_spriteBatch->Draw(m_orion_damage_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
			break;

		}
	}
	m_spriteBatch->End();

	//���C���[�̕`��
	for (int i = 0; i < WIRE_NUM; i++)
	{
		if (m_wire[i] != nullptr)
		{
			m_wire[i]->Render(m_wire_posX[i]);
		}
	}
}

//��------------------------------------------------------------------��
//��*func�F���C���[���擾�im_wire[i]�j
//��*arg�F���ڂ��ii�j
//��*return�F���C���[�Bnullptr�Ȃ�nullptr��Ԃ�
//��*heed�FGamePlay�Ŏg�p
//��------------------------------------------------------------------��
Wire * Player::GetWire(int i)
{
	if (m_wire[i] != nullptr)
	{
		return m_wire[i];
	}

	return nullptr;
}

//��------------------------------------------------------------------��
//��*func�F���C���[�𔭎˂���
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*heed�F�X�y�[�X�L�[�������ꂽ��Ăяo��
//��------------------------------------------------------------------��
void Player::WireShot()
{
	for (int i = 0; i < WIRE_NUM; i++)
	{
		//���C���[������ĂȂ�������
		if (m_wire[i] == nullptr)
		{
			m_wire[i] = new Wire(m_posX);
			m_wire_posX[i] = m_posX;
			break;
		}
	}

}

//��------------------------------------------------------------------��
//��*func�F���C���[�����ł�����֐�
//��*arg�F���ڂ̃��C���[��(i�j
//��*return�F�Ȃ�
//��*heed�F���Ђ��L���b�`������GamePlay�ŌĂяo��
//��------------------------------------------------------------------��
void Player::Elimination(int i)
{
	m_wire[i]->Elimination();
}

//��------------------------------------------------------------------��
//��*func�F�_���[�W��Ԃɂ���
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Player::Damage()
{
	m_state = DAMAGE;
}

//��------------------------------------------------------------------��
//��*func�F��Ԃ��擾����
//��*arg�F�Ȃ�
//��*return�Fm_state
//��------------------------------------------------------------------��
int Player::State()
{
	return m_state;
}








