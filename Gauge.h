//**********************************//
//*	���@�O�FGauge.h
//*	���@�e�F���Ќv�ʃQ�[�W�N���X
//*	���@�t�F2017.05.24
//* �X�V���F2017.06.02
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
	void Update();								//�X�V
	void Render();								//�`��
	void addGradation(int state);				//�Q�[�W�𑝂₷
	int getGradation();							//�Q�[�W�̒l�擾

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	//	�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hourglassTex;	//�����v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_colorTex;		//�Q�[�W�F

	//	�e�N�X�`�����_
	DirectX::SimpleMath::Vector2 m_origin;				//�����v
	DirectX::SimpleMath::Vector2 m_gradationOrigin;		//�Q�[�W�F

	//	�\�����W
	DirectX::SimpleMath::Vector2 m_screenPos;			//�����v
	DirectX::SimpleMath::Vector2 m_gradationPos;		//�Q�[�W�F

	//	�Q�[�W�̖ڐ��萔�l(�O���f�[�V����)
	int m_gradation;

};
