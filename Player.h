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


//�L�����̕��A����
const int GRP_WIDTH = 96;
const int GRP_HEIGHT = 96;

enum
{
	NORMAL,		//�ʏ�
	UP,			//�㏸
	DOWN,		//���~
	DIE,		//���S
};

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

	//*posY���擾����֐�
	float Pos_y();

	//*Render�֐�
	void Render();

private:
	//���v�̈ꎟ�֐������߂邽�߂̕ϐ�
	float a;	//y=ax+b��a�i�X���j
	float b;	


	bool jump_flug;		//�W�����v�t���O
	bool jump_judge_flug;

	float m_y_prev;		//�W�����v�p�B�L�����̂����W��ۑ�
	float m_y_temp;		//�W�����v�p�B�L�����̂����W��ۑ�
	float m_y_render;		//���C���[��Render�p

	Wire* wire;			//���C���[

	//�`��
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_orion_normal_tex;	//�ʏ펞�e�N�X�`��


};

