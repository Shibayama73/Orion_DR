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

class Fragment :
	public ObjectBase
{
public:
	Fragment();
	~Fragment();
	void Update();
	void Render();

	bool Outdoor();		//��ʓ��Ɍ��Ђ����邩�ǂ���

public:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fragment_tex;	//�ʏ펞�e�N�X�`��


};

