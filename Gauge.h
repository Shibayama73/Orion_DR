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
#include "Fragment.h"

class Gauge:public ObjectBase
{
public:
	Gauge();
	~Gauge();
	void Update();									//�X�V
	void Render();									//�`��
	void addGradation(int state);				//�Q�[�W�𑝂₷

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	//	�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bottleTex;	//�r
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_colorTex;	//���АF

	//	�e�N�X�`�����_
	DirectX::SimpleMath::Vector2 m_origin;
	DirectX::SimpleMath::Vector2 m_gradationOrigin;
	//	�\�����W
	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_gradationPos;

	//	�Q�[�W�̖ڐ��萔(�O���f�[�V����)
	int m_gradation;

};
