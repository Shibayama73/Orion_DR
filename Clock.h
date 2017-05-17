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
	DirectX::SimpleMath::Vector2 m_shotTipPos;		//�Z�j�̐�[���W

public:
	Clock();
	~Clock();
	void Update();									//�X�V
	void Render();									//�`��
	bool getHand();									//�j�̏�Ԏ擾
	DirectX::SimpleMath::Vector2 getLongTipPos();	//�j�̐�[���W�擾
	DirectX::SimpleMath::Vector2 getShotTipPos();	//�j�̐�[���W�擾
	void clockwise();								//�j���E���ɓ�����

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;	//�e�N�X�`��2

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;


};