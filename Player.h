//��----------------------------------------------------��
//��*�t�@�C�����FPlayer.cpp								��
//��*���e�@�@�@�F�v���C���[�N���X						��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.01								��
//��----------------------------------------------------��

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

#include "Wire.h"


//�L�����̐��l
const int GRP_WIDTH = 128;
const int GRP_HEIGHT = 128;

enum STATE
{
	NORMAL,		//�ʏ�
	DIE,		//���S
};

enum VEC
{
	LEFT,
	RIGHT,
};

enum ANIMATEION
{
	UP,
	DOWN,
};

//�v���C���[���������Ă����x�ɏo���郏�C���[�̐�
const int WIRE_NUM = 3;

class Player :public ObjectBase
{
public:
	Player();
	~Player();

	//*�j�����擾����֐�
	void Needle(DirectX::SimpleMath::Vector2 needle, DirectX::SimpleMath::Vector2 tip_origin);

	//*������Ă���j�̒������擾����֐�
	bool Length(bool length);

	//*�j�̗L�����擾����֐�
	bool Existence(DirectX::SimpleMath::Vector2 needle, DirectX::SimpleMath::Vector2 tip_origin);

	//*����֐�
	void run(DirectX::SimpleMath::Vector2 needle, DirectX::SimpleMath::Vector2 tip_origin);

	//*Render�֐�
	void Render();

	//*���C���[�̏����擾
	Wire* GetWire(int i);

	void Elimination(int i);		//���C���[�����ł�����֐�


private:
	//���v�̈ꎟ�֐������߂邽�߂̕ϐ�
	float a;	//y=ax+b��a�i�X���j
	float b;	

	bool m_vec;		//�����i�O�F���A�P�F�E�j

	bool m_jump_flug;		//�W�����v�t���O
	bool m_jump_judge_flug;
	bool m_animetion;	//0��UP�A1��DOWN
	int time_cnt;

	float m_y_prev;		//�W�����v�p�B�L�����̂����W��ۑ�
	float m_y_temp;		//�W�����v�p�B�L�����̂����W��ۑ�
	float m_y_render;		//���C���[��Render�p

	Wire* m_wire[WIRE_NUM];			//���C���[

	float m_wire_posX[WIRE_NUM];



	//�`��
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_orion_normal_tex;	//�ʏ펞�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_orion_normal_left_tex;	//�ʏ펞�������e�N�X�`��

};

