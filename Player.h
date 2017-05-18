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
	void Needle(DirectX::SimpleMath::Vector2 needle);

	//*�j�̗L�����擾����֐�
	bool Existence(bool length);

	//*����֐�
	void run();

	//*Render�֐�
	void Render();

private:
	float a;	//y=ax+b��a�i�X���j

	//�`��
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_orion_normal_tex;	//�ʏ펞�e�N�X�`��


};

