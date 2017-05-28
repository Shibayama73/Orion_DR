//**********************************//
//*	GamePlay.cpp
//*	�v���C�V�[��
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#include "GamePlay.h"
#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

#include "Game.h"
#include "pch.h"
#include <WICTextureLoader.h>

//	�T�E���h
#include "Resouces\Music\CueSheet_0.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

GamePlay::GamePlay()
{
	//m_TimeCnt = 0;

	//���Ԃ̐���
	m_time = new Time();
	//	���v����
	m_clock = new Clock();

	//�v���C���[�̐���
	m_player = new Player();

	//���Ђ̐���
	for (int i = 0; i < FRAGMENT_MAX; i++)
	{
		m_fragment[i] = new Fragment();
	}

	//	�Q�[�W�̐���
	m_gauge = new Gauge();

	//�������Z�p�ϐ��̏�����
	m_time_flag = 0;

	////	�`��ǂݍ���============================================================================
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/background_play.jpg",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> backgraund;
	DX::ThrowIfFailed(resource.As(&backgraund));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC backgraundDesc;
	backgraund->GetDesc(&backgraundDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(backgraundDesc.Width / 2.0f);
	m_origin.y = float(backgraundDesc.Height / 2.0f);

	//	�\�����W����ʒ����Ɏw��
	m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	////==========================================================================================

	//	�T�E���h�t�@�C���̓ǂݍ���
	ADX2Le::Initialize("Resouces/Music/OrionMusic.acf");
	ADX2Le::LoadAcb("Resouces/Music/CueSheet_0.acb", "Resouces/Music/CueSheet_0.awb");

	//	�T�E���h�Đ�
	ADX2Le::Play(CRI_CUESHEET_0_PLAY);

}

GamePlay::~GamePlay()
{
	//	���v�j��
	delete m_clock;

	//�v���C���[�̔j��
	delete m_player;

	//���Ђ̔j��
	for (int i = 0; i < FRAGMENT_MAX; i++)
	{
		delete m_fragment[i];
	}

	//	�Q�[�W�̔j��
	delete m_gauge;

	//���v�̔j��
	delete m_time;

	//	�T�E���h���C�u�����̏I������
	ADX2Le::Finalize();

}

int GamePlay::UpdateGame()
{
	m_NextScene = PLAY;
	m_scene = PLAY;

	//�e�N���X�̍X�V===============================================//
	//	�T�E���h�̍X�V
	ADX2Le::Update();

	//	���v�̍X�V
	m_clock->Update();

	//m_time->CurrentTime();

	//���j��12���̂Ƃ���ɗ�����A���ݎ�����ǉ�
	if (m_clock->LongAngle() == 270)
	{
		if (m_time_flag == 0)
		{
			m_time->CurrentTime();
		}
		m_time_flag++;

		if (m_time_flag > 3)
		{
			m_time_flag = 0;
		}

	}

	//m_player->Needle(m_clock->getLongTipPos(), m_clock->getLongTipOrigin());
	//	�v���C���[�̈ړ�����
	m_player->run(m_clock->getLongTipPos(), m_clock->getOrigin());

	//	�v���C���[�̍X�V
	m_player->Update();

	//�X�y�[�X�L�[�Ń��C���[
	if (g_keyTracker->pressed.Space)
	{
		m_player->WireShot();
		//	���ʉ�
		ADX2Le::Play(CRI_CUESHEET_0_THROW);
	}


	//�v���C���[�̏������Ă��郏�C���[�̕ۊ�
	for (int i = 0; i < WIRE_NUM; i++)
	{
		m_player_wire[i] = m_player->GetWire(i);
	}

	//���Ђ̍X�V
	for (int i = 0; i < FRAGMENT_MAX; i++)
	{
		m_fragment[i]->Update(m_clock->getOrigin());

		//	���Ђ��͂܂ꂽ��Ԃ̂Ƃ�
		if (m_fragment[i]->State() == FRAGMENT_CATCH)
		{
		//��-------------------------------------------------------------------------------------------------------------------��//
		//���j�ƌ��Ђ̓����蔻��

			float under_angle;			//*���j�ƒZ�j�̊Ԃ̊p
			float under_angle2;			//*�Z�j�ƒ��j�̊Ԃ̊p
			float long_angle;			//*���j�ƌ��_�̊Ԃ̊p�x
			float short_angle;			//*�Z�j�ƌ��_�̊Ԃ̊p�x

			float big_angle;			//*�傫������p�B���j�ƒZ�j���ׂđ傫�����̊p�x����
			float small_angle;			//*�傫������p�B���j�ƒZ�j���ׂď��������̊p�x����
			float null_angle;			//*����ւ��p

			//���j�ƌ��_�̊Ԃ̊p�x����
			long_angle = m_clock->LongAngle();
			//�Z�j�ƌ��_�̊Ԃ̊p�x����
			short_angle = m_clock->ShortAngle();

			//���j�̊p�x-�Z�j�̊p�x
			under_angle = long_angle - short_angle;
			//�Z�j�̊p�x-���j�̊p�x
			under_angle2 = short_angle - long_angle;

			//���ꂼ��̊Ԃ̊p�x��180�x�ȏ�̏ꍇ�A�t���̊p�x�����߂đ������
			if (under_angle > 180)
			{
				under_angle = (360 - long_angle) + short_angle;
			}
			if (under_angle2 > 180)
			{
				under_angle2 = (360 - short_angle) + long_angle;
			}


			//���j�̊p�x�ƒZ�j�̊p�x���ׂāA�傫������big�A����������short�ɑ��
			if (long_angle > short_angle)
			{
				big_angle = long_angle;
				small_angle = short_angle;
			}
			else
			{
				big_angle = short_angle;
				small_angle = long_angle;
			}

			//�傫�����̊p��301�x�ȏ�ŁA�X�ɏ��������̊p��60�x�����̏ꍇ�A���������̊p��360�����āA�傫�����Ə������������ւ���
			//�����_�Ƃ̊Ԃ̊p��0�`60�̎��Ɍ��Ђ����ނ��Ƃ��o���Ȃ��Ȃ�o�O�h�~�̂���
			if (big_angle > 301 && small_angle < 60)
			{
				small_angle += 360;
				null_angle = big_angle;
				big_angle = small_angle;
				small_angle = big_angle;
			}

			//���j�ƒZ�j�̊Ԃ̊p��60�x�ȉ��̏ꍇ�̂ݔ���
			if (under_angle > 0 && under_angle < 60)
			{
				//���������̐j�̊p�x�������Ђ̊p�x���傫���A���傫���j�̊p�x�������Ђ̊p�x���������ꍇ
				if ((small_angle < m_fragment[i]->Angle(m_clock->getOrigin())) && (big_angle > m_fragment[i]->Angle(m_clock->getOrigin())))
				{
					//	���Ђ���������
					m_fragment[i]->AttackTip();
					//	���ʉ�
					ADX2Le::Play(CRI_CUESHEET_0_VANISH);
					//	�Q�[�W���J�E���g�����
					m_gauge->addGradation(m_fragment[i]->State());

				}
			}
			//�Z�j�ƒ��j�̊Ԃ̊p��60�x�ȉ��̏ꍇ�̂ݔ���
			if (under_angle2 > 0 && under_angle2 < 60)
			{
				//���������̐j�̊p�x�������Ђ̊p�x���傫���A���傫���j�̊p�x�������Ђ̊p�x���������ꍇ
				if ((big_angle > m_fragment[i]->Angle(m_clock->getOrigin())) && (small_angle < m_fragment[i]->Angle(m_clock->getOrigin())))
				{
					//	���Ђ���������
					m_fragment[i]->AttackTip();
					//	���ʉ�
					ADX2Le::Play(CRI_CUESHEET_0_VANISH);
					//	�Q�[�W���J�E���g�����
					m_gauge->addGradation(m_fragment[i]->State());

				}
			}
		//��-------------------------------------------------------------------------------------------------------------------��//
		}

		//���Ђ������Ă�����
		if (m_fragment[i]->State() == FRAGMENT_LOSS)
		{
			//�j�����ĐV���ɐ�������
			delete m_fragment[i];
			m_fragment[i] = new Fragment();
		}
	}

	//���C���[�ƌ��Ђ̓����蔻��i���C���[�̏����݂̂ŁA���Ђ̏����͊֐����Łj
	for (int i = 0; i < WIRE_NUM; i++)
	{
		for (int j = 0; j < FRAGMENT_MAX; j++)
		{
			//���C���[�ƌ��ЁA���ꂼ�ꑶ�݂��Ă��邩�m�F
			if (m_player_wire[i] != nullptr && m_fragment[j] != nullptr)
			{
				//���C���[�ɓ������Ă�����
				if (m_fragment[j]->Collision(m_player_wire[i]))
				{
					//���C���[�����ł�����
					m_player->Elimination(i);

					//	���ʉ�
					ADX2Le::Play(CRI_CUESHEET_0_HIT);
				}
			}

		}
	}


	//�c�莞�Ԃ��O�ɂȂ�����
	if (!(m_time->RemnantTime()))
	{
		FileIO(1, m_gauge->getGradation());
		m_NextScene = OVER;
	}
	return m_NextScene;
}

void GamePlay::RenderGame()
{
	////	�X�v���C�g�̕`��========================================================================
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();
	////==========================================================================================
	//	���v�`��
	m_clock->Render();

	//���Ђ̕`��
	for (int i = 0; i < FRAGMENT_MAX; i++)
	{
		m_fragment[i]->Render();
	}

	//�v���C���[�̕`��
	m_player->Render();

	//	�Q�[�W�̕`��
	m_gauge->Render();

	//���Ԃ̕`��
	m_time->Render();


}

//��------------------------------------------------------------------��
//��*func�F�t�@�C���ǂݏ����֐�
//��*arg�F�ǂݏ����w��i�O�F�ǂݍ��݁A�P�F�������݁j�A�ǂݏ����������ϐ�
//��*return�F����i�O�j�A�G���[�i�P�j
//��------------------------------------------------------------------��
int GamePlay::FileIO(int io, int score)
{
	char *Filename = "data.txt";
	FILE *fp;

	if (io == 0)
	{
		//�ǂݍ���
		fp = fopen(Filename, "r");
		if (fp == NULL)
		{
			return 1;
		}
		fscanf(fp, "%d", &score);
	}
	else
	{
		//��������
		fp = fopen(Filename, "w");
		if (fp == NULL)
		{
			return 1;
		}
		fprintf(fp, "%d", score);
	}
	fclose(fp);
	return 0;
}

