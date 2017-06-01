//��----------------------------------------------------��
//��*�t�@�C�����FWire.h									��
//��*���e�@�@�@�F���C���[								��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.18								��
//��----------------------------------------------------��
#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"


class Wire : public ObjectBase
{
public:
	Wire(float posX);
	~Wire();

	void Update(float pos_x);

	void Render(float pos_x);

	void Elimination();		//���ł�����

	bool State();		//�\�����̎擾

private:
	//�`��
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_wire_tex;	//�ʏ펞�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_wire_L_tex;	//�ʏ펞���e�N�X�`��

	bool m_state;		//�\������Ă��邩�A��\���ɂȂ��Ă��邩�itrue�F�\���Afalse�F��\���j
	bool m_elimination; //���ł��Ă��邩�ۂ�
};

