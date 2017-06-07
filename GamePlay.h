//**********************************//
//*	���@�O�FGamePlay.h
//*	���@�e�F�v���C�V�[��
//*	���@�t�F2017.04.25
//* �X�V���F2017.06.02
//*	����ҁFN.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

#include "Clock.h"
#include "Player.h"
#include "Wire.h"
#include "Fragment.h"
#include "Gauge.h"
#include "Time.h"
#include "Screw.h"
#include "Effect.h"

#include "ADX2Le.h"

const int FRAGMENT_MAX = 20;

class GamePlay :public GameBase
{
public:
	GamePlay();			//	�R���X�g���N�^
	~GamePlay();		//	�f�X�g���N�^
	int UpdateGame();	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��

	//�t�@�C���ǂݏ���
	int FileIO(int io, int score);


private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//�e�N�X�`��

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	Clock* m_clock;		//���v
	Player* m_player;	//�v���C���[
	Wire* m_player_wire[WIRE_NUM];		//���C���[�i�v���C���[�̏������Ă��郏�C���[���ꎞ�I�ɕۊǂ���j
	Fragment* m_fragment[FRAGMENT_MAX];	//����
	Effect* m_effect[FRAGMENT_MAX];
	Gauge* m_gauge;		//�Q�[�W
	Time* m_time;			//����
	Screw* m_screw;		//�l�W

	int m_time_flag;		//�������Z�p�ϐ�
	int m_effect_time;
};
