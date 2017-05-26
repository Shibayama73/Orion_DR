//**********************************//
//*	���@�O�FClock.h
//*	���@�e�F���v�N���X
//*	���@�t�F2017.5.2
//*	����ҁFN.Shibayama
//**********************************//

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

class Clock :public ObjectBase
{
protected:
	bool m_hand;									//���v�̐j(���j(true)�A�Z�j(false))
	DirectX::SimpleMath::Vector2 m_longTipPos;		//���j�̐�[���W
	DirectX::SimpleMath::Vector2 m_shortTipPos;		//�Z�j�̐�[���W

public:
	Clock();
	~Clock();
	void Update();									//�X�V
	void Render();									//�`��

	bool getHand();										//�j�̏�Ԏ擾
	DirectX::SimpleMath::Vector2 getOrigin();			//���j�̌��_���W�擾
	DirectX::SimpleMath::Vector2 getLongTipPos();		//�j�̐�[���W�擾
	DirectX::SimpleMath::Vector2 getShortTipPos();		//�j�̐�[���W�擾
	void clockwise();									//�j���E���ɓ�����
	//float calAngle(DirectX::SimpleMath::Vector2 origin,
	//	DirectX::SimpleMath::Vector2 longTip,
	//	DirectX::SimpleMath::Vector2 shortTip);			//3�_�̍��W����Ȃ��p)�̌v�Z

	//�f�o�b�N�p���l
	void DrawNum(float x, float y, int n);


private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	//	�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clockTex;	//���v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_LongTipTex;	//���j
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShortTipTex;	//�Z�j
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_OriginTex;	//���_

	//	�\�����W
	DirectX::SimpleMath::Vector2 m_screenPos;	//���v���_

	//	�e�N�X�`�����_
	DirectX::SimpleMath::Vector2 m_origin;		//���v
	DirectX::SimpleMath::Vector2 m_longTOri;	//���j
	DirectX::SimpleMath::Vector2 m_shortTOri;	//�Z�j
	DirectX::SimpleMath::Vector2 m_ori;			//���_

	//	��]
	float m_rotLongPos;		//���j��]
	float m_rotShortPos;	//�Z�j��]
	//	���W�p�x
//	float m_LTPos;		//���j���W�p�x
//	float m_STPos;		//�Z�j���W�p�x

	//�f�o�b�N�p
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_time_tex;	//�ʏ펞�e�N�X�`��



};