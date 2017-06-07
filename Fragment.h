//��----------------------------------------------------��
//��*�t�@�C�����FFragment.h								��
//��*���e�@�@�@�F���ЃN���X								��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.22 							��
//��----------------------------------------------------��

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

enum
{
	FRAGMENT_NORMAL,
	FRAGMENT_CATCH,
	FRAGMENT_LOSS,
};

class Fragment :
	public ObjectBase
{
public:
	Fragment();
	~Fragment();
	void Update();
	void Render();

	void Outdoor();		//��ʓ��Ɍ��Ђ����邩�ǂ���

	int State();		//���Ђ̏�Ԏ擾

	bool Collision(ObjectBase * A);		//�����蔻��

	float Angle(DirectX::SimpleMath::Vector2 tip_origin);				//���Ђ̂���p�x

	void AttackTip();		//�j�Ɠ��������ۂɐj�Ɠ��������ɓ�������


private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fragment_tex;	//�ʏ펞�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fragment_catch_tex;	//�L���b�`��e�N�X�`��


	float m_fragmentLongAngle;		//�p�x�i���j�Ƃ̓����蔻��p
	float m_fragmentShortAngle;		//�p�x�i�Z�j�Ƃ̓����蔻��p

	bool m_effect_state;

};
