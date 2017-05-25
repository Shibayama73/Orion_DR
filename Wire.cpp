//��----------------------------------------------------��
//��*�t�@�C�����FWire.cpp								��
//��*���e�@�@�@�F���C���[								��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.18								��
//��----------------------------------------------------��

#include "pch.h"
#include "Wire.h"

#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

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
Wire::Wire()
{

	m_state = true;		//�\�����
	m_posY = 650;

	m_grpH = 64.0f;
	m_grpW = 64.0f;
	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�ʏ펞�摜
	ComPtr<ID3D11Resource> wire_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/wire.png",
			wire_resource.GetAddressOf(),
			m_wire_tex.ReleaseAndGetAddressOf()));



	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> wire;
	DX::ThrowIfFailed(wire_resource.As(&wire));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC wireDesc;
	wire->GetDesc(&wireDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(wireDesc.Width / 2.0f);
	m_origin.y = float(wireDesc.Height / 2.0f);



}

//��------------------------------------------------------------------��
//��*func�F�f�X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
Wire::~Wire()
{
}

//��------------------------------------------------------------------��
//��*func�F�X�V
//��*arg�F�v���C���[�̍��Wx
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Wire::Update(float pos_x)
{
	if (m_state)
	{
		m_posX = pos_x;
		m_posY -=2;
	}
	if (m_state && m_posY < 0)
	{
		Elimination();
	}
}

//��------------------------------------------------------------------��
//��*func�F�`��֐�
//��*arg�F�v���C���[�̍��Wx
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Wire::Render(float pos_x)
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	if (m_state)
	{
		m_spriteBatch->Draw(m_wire_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
	}
	m_spriteBatch->End();


}

//��------------------------------------------------------------------��
//��*func�F���ł�����֐��im_state�j
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*heed�F��ʊO�ɏo������ł�����A�������́A���Ђ��L���b�`������
//��------------------------------------------------------------------��
void Wire::Elimination()
{
	m_state = false;
}

//��------------------------------------------------------------------��
//��*func�F�\�����̎擾�֐��im_state�j
//��*arg�F�Ȃ�
//��*return�Fm_state
//��------------------------------------------------------------------��
bool Wire::State()
{
	return m_state;
}


