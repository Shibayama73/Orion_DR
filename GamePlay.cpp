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


	////	�`��ǂݍ���============================================================================
	//m_deviceResources = Game::m_deviceResources.get();
	//m_spriteBatch = Game::m_spriteBatch.get();

	//ComPtr<ID3D11Resource> resource;
	//DX::ThrowIfFailed(
	//	CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/clock.png",
	//		resource.GetAddressOf(),
	//		m_texture.ReleaseAndGetAddressOf()));

	////	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	//ComPtr<ID3D11Texture2D> clock;
	//DX::ThrowIfFailed(resource.As(&clock));

	////	�e�N�X�`�����
	//CD3D11_TEXTURE2D_DESC clockDesc;
	//clock->GetDesc(&clockDesc);

	////	�e�N�X�`�����_���摜�̒��S�ɂ���
	//m_origin.x = float(clockDesc.Width / 2.0f);
	//m_origin.y = float(clockDesc.Height / 2.0f);

	////	�\�����W����ʒ����Ɏw��
	//m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	//m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;

	////==========================================================================================

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

}

int GamePlay::UpdateGame()
{
	m_NextScene = PLAY;
	m_scene = PLAY;

	//	�e�N���X�̍X�V
	//	���v�̍X�V
	m_clock->Update();
	m_time->CurrentTime();

	if (m_clock->getLongTipPos().x == 450 && m_clock->getLongTipPos().y == 0)
	{
		delete m_player;
	}
	//m_player->Needle(m_clock->getLongTipPos(), m_clock->getLongTipOrigin());
	//	�v���C���[�̈ړ�����
	m_player->run(m_clock->getLongTipPos(), m_clock->getOrigin());

	//	�v���C���[�̍X�V
	m_player->Update();

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
			//	���_�A���j�A���Ђ̍��W����p�x���Z�o����
			float longTipAngle = m_clock->calAngle(m_clock->getOrigin(), m_clock->getLongTipPos(), Vector2(m_fragment[i]->GetPosX(), m_fragment[i]->GetPosY()));
			//	���_�A�Z�j�A���Ђ̍��W����p�x���Z�o����
			float shortTipAngle = m_clock->calAngle(m_clock->getOrigin(), m_clock->getShortTipPos(), Vector2(m_fragment[i]->GetPosX(), m_fragment[i]->GetPosY()));

			//	���j�ƌ��Ђ̊p�x����v�����Ƃ�
			if (longTipAngle == 0.0f)
			{
				//	���Ђ����j�Ɠ��������Ɉړ�����
				float fragment_angle = XMConvertToDegrees(m_clock->calAngle(m_clock->getOrigin(), m_clock->getLongTipPos(), m_clock->getShortTipPos()));
				m_fragment[i]->AttackTip(fragment_angle);
			}
			//	�Z�j�ƌ��Ђ̊p�x����v�����Ƃ�
			if (shortTipAngle == 0.0f)
			{
				//	���Ђ��Z�j�Ɠ��������Ɉړ�����
				float fragment_angle = XMConvertToDegrees(m_clock->calAngle(m_clock->getOrigin(), m_clock->getLongTipPos(), m_clock->getShortTipPos()));
				m_fragment[i]->AttackTip(fragment_angle);
			}
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
				}
			}

		}
	}
	

	//�c�莞�Ԃ��O�ɂȂ�����
	//if (!(m_time->RemnantTime()))
	//{
	//	m_NextScene = OVER;
	//}
	return m_NextScene;
}

void GamePlay::RenderGame()
{
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




	////	�X�v���C�g�̕`��========================================================================
	//CommonStates m_states(m_deviceResources->GetD3DDevice());
	//m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	//m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);

	//m_spriteBatch->End();
	////==========================================================================================

}

