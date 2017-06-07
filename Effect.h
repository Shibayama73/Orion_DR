//��----------------------------------------------------��
//��*�t�@�C�����FEffect.h								��
//��*���e�@�@�@�F�G�t�F�N�g�N���X						��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.06.05								��
//��----------------------------------------------------��

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"


enum
{
	EFFECT_OFF,
	EFFECT_ON,
	EFFECT_LOSS,
};

class Effect : public ObjectBase
{
public:
	//*�R���X�g���N�^
	Effect();
	//*�f�X�g���N�^
	~Effect();
	//*�X�V�֐�
	void Update();
	//*�`��֐�
	void Render();
	//*state��ON�ɂ���
	void ChengeState(float posX, float posY);
	//*state��Loss�ɂ���
	void EffectLoss();
	//*state���擾����
	int State();

private:
	//*�`��p
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_effect_tex;	//�G�t�F�N�g�p�e�N�X�`��

	//*�G�t�F�N�g�p�J�E���g
	int m_cnt;

};

