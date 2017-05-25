//**********************************//
//*	GamePlay.h
//*	�v���C�V�[��
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
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

const int FRAGMENT_MAX = 6;

class GamePlay :public GameBase
{
public:
	GamePlay();			//	�R���X�g���N�^
	~GamePlay();		//	�f�X�g���N�^
	int UpdateGame();	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��


private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//�e�N�X�`��

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	Clock* m_clock;		//���v
	Player* m_player;	//�v���C���[
	Wire* m_player_wire[WIRE_NUM];		//���C���[�i�v���C���[�̏������Ă��郏�C���[���ꎞ�I�ɕۊǂ���j
	Fragment* m_fragment[FRAGMENT_MAX];	//���Ёi������6�ȏ�o���Ȃ��j
	Gauge* m_gauge;		//�Q�[�W

};
