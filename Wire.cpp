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

	m_state = false;		//��\�����

	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�ʏ펞�摜
	ComPtr<ID3D11Resource> wire_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/wire.png",
			wire_resource.GetAddressOf(),
			m_wire_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/wire_L.png",
			wire_resource.GetAddressOf(),
			m_wire_L_tex.ReleaseAndGetAddressOf()));



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
//��*func�F�`��֐�
//��*arg�F�v���C���[�̍��Wy
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Wire::Render(float pos_y, bool player_vec)
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	if (m_state)
	{
		switch (player_vec)
		{
		case LEFT:
			m_spriteBatch->Draw(m_wire_L_tex.Get(), Vector2(700, pos_y), nullptr, Colors::White, 0.f, m_origin);
			break;
		case RIGHT:
			m_spriteBatch->Draw(m_wire_tex.Get(), Vector2(700, pos_y), nullptr, Colors::White, 0.f, m_origin);
			break;
		}

	}
	m_spriteBatch->End();


}

//��------------------------------------------------------------------��
//��*func�F�\��������֐��im_state�j
//��*arg�F�Ȃ�
//��*return�Fm_state
//��*heed�F���C���[���o�������������true�ɂ���B
//��------------------------------------------------------------------��
bool Wire::Appears()
{
	if (!m_state)
	{
		m_state = true;
	}
	return m_state;
}


