//��----------------------------------------------------��
//��*�t�@�C�����FEffect.cpp								��
//��*���e�@�@�@�F�G�t�F�N�g�N���X						��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.06.05								��
//��----------------------------------------------------��

#include "pch.h"
#include "Effect.h"

#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>
#include <Math.h>

#include "Game.h"
#include "pch.h"
#include <WICTextureLoader.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


//��------------------------------------------------------------------��
//��*func�F�R���X�g���N�^
//��*arg�F�Ȃ�
//��------------------------------------------------------------------��
Effect::Effect()
{
	m_state = EFFECT_OFF;

	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�G�t�F�N�g�p�摜
	ComPtr<ID3D11Resource> effect_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/kirakira.png",
			effect_resource.GetAddressOf(),
			m_effect_tex.ReleaseAndGetAddressOf()));


	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> effect;
	DX::ThrowIfFailed(effect_resource.As(&effect));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC effectDesc;
	effect->GetDesc(&effectDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(effectDesc.Width / 2.0f);
	m_origin.y = float(effectDesc.Height / 2.0f);

	m_cnt = 0;
}


//��------------------------------------------------------------------��
//��*func�F�f�X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��

Effect::~Effect()
{
}

//��------------------------------------------------------------------��
//��*func�F�X�V�֐�
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*heed�F�Ȃ�
//��------------------------------------------------------------------��

void Effect::Update()
{
	//�G�t�F�N�g��ON�̎�
	if (m_state == EFFECT_ON)
	{
		m_cnt++;
		//60�t���[���o���������
		if (m_cnt > 60)
		{
			EffectLoss();
		}
	}
}


//��------------------------------------------------------------------��
//��*func�F�`��֐�
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*heed�F�Ȃ�
//��------------------------------------------------------------------��

void Effect::Render()
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	if (m_state == EFFECT_ON)
	{
   		m_spriteBatch->Draw(m_effect_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
		m_spriteBatch->Draw(m_effect_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
	}
	m_spriteBatch->End();

}

//��------------------------------------------------------------------��
//��*func�F�G�t�F�N�g��state��on�ɂ���֐�
//��*arg�F���Ђ̈ʒu(float posX,float posY)
//��*return�F�Ȃ�
//��------------------------------------------------------------------��

void Effect::ChengeState(float posX, float posY)
{
	m_posX = posX;
	m_posY = posY;

	m_state = EFFECT_ON;
}

//��------------------------------------------------------------------��
//��*func�F�G�t�F�N�g��state��loss�ɂ���֐�
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Effect::EffectLoss()
{
	m_state = EFFECT_LOSS;
}

//��------------------------------------------------------------------��
//��*func�F�G�t�F�N�g��state���擾����֐�
//��*arg�F�Ȃ�
//��*return�Fm_state
//��------------------------------------------------------------------��
int Effect::State()
{
	return m_state;
}


