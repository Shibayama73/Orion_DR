//**********************************//
//*	���@�O�FGauge.h
//*	���@�e�F���Ќv�ʃQ�[�W�N���X
//*	���@�t�F2017.5.24
//*	����ҁFN.Shibayama
//**********************************//

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

class Gauge:public ObjectBase
{
public:
	Gauge();
	~Gauge();
	void Update();									//�X�V
	void Render();									//�`��


private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	//	�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bottleTex;	//�r
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_colorTex;	//���АF

	//	�e�N�X�`�����_
	DirectX::SimpleMath::Vector2 m_origin;
	//	�\�����W
	DirectX::SimpleMath::Vector2 m_screenPos;



};
