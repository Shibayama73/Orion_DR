//��----------------------------------------------------��
//��*�t�@�C�����FScrew.h								��
//��*���e�@�@�@�F�l�W�N���X								��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.06.01								��
//��----------------------------------------------------��

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

enum 
{
	SCREW_NORMAL,
	SCREW_LOSS,
};

class Screw :
	public ObjectBase
{

public:
	Screw();
	~Screw();
	void Update();
	void Render();

	void Outdoor();		//��ʓ��Ɍ��Ђ����邩�ǂ���

	bool Collision(ObjectBase * A);		//�����蔻��

	int State();		//��Ԃ̊m�F

	void AttackTip();

public:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_screw_tex;	//�ʏ펞�e�N�X�`��


};

