//��----------------------------------------------------��
//��*�t�@�C�����FFragment.cpp							��
//��*���e�@�@�@�F���ЃN���X								��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.22 							��
//��----------------------------------------------------��


#include "pch.h"
#include "Fragment.h"

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
Fragment::Fragment()
{
	m_posX = rand() % 470 + 200;
	m_posY = (rand() % -1000) - 1010;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpW = 32;
	m_grpH = 32;

	m_state = FRAGMENT_NORMAL;

	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�ʏ펞�摜
	ComPtr<ID3D11Resource> fragment_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/star.png",
			fragment_resource.GetAddressOf(),
			m_fragment_tex.ReleaseAndGetAddressOf()));
	//�L���b�`��摜
	ComPtr<ID3D11Resource> fragment_catch_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/star_catch.png",
			fragment_catch_resource.GetAddressOf(),
			m_fragment_catch_tex.ReleaseAndGetAddressOf()));


	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> fragment;
	DX::ThrowIfFailed(fragment_resource.As(&fragment));
	DX::ThrowIfFailed(fragment_catch_resource.As(&fragment));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC fragmentDesc;
	fragment->GetDesc(&fragmentDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(fragmentDesc.Width / 2.0f);
	m_origin.y = float(fragmentDesc.Height / 2.0f);


}


//��------------------------------------------------------------------��
//��*func�F�f�X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
Fragment::~Fragment()
{
}

//��------------------------------------------------------------------��
//��*func�F�X�V����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Fragment::Update(DirectX::SimpleMath::Vector2 origin)
{
	m_spdY += 0.01;
	m_posY += m_spdY;
	m_posX += m_spdX;

	if (m_state == FRAGMENT_CATCH)
	{
		if (origin.y > m_posY)
		{
			m_spdY = 0.1f;
		}
		else if (origin.y < m_posY)
		{
			m_spdY = -0.1f;
		}
		else
		{
			m_spdX = 0;
			m_spdY = 0;
		}
	}


	//��O�ɏo�Ă��邩�̔���
	Outdoor();
}

//��------------------------------------------------------------------��
//��*func�F�`�揈��
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Fragment::Render()
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	switch (m_state)
	{
	case FRAGMENT_NORMAL:
		m_spriteBatch->Draw(m_fragment_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
		break;

	case FRAGMENT_CATCH:
		m_spriteBatch->Draw(m_fragment_catch_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);
		break;
	}
	

	m_spriteBatch->End();

}

//��------------------------------------------------------------------��
//��*func�F��ʓ��Ɍ��Ђ����邩�ǂ���
//��*arg�F�Ȃ�
//��*return�Ftrue�i����j�Afalse�i�Ȃ��j
//��------------------------------------------------------------------��
void Fragment::Outdoor()
{
	if (m_posY + m_grpH > 700)
	{
		m_state = FRAGMENT_LOSS;
	}

}

//��------------------------------------------------------------------��
//��*func�F�\�����̎擾�֐��im_state�j
//��*arg�F�Ȃ�
//��*return�Fm_state
//��------------------------------------------------------------------��
int Fragment::State()
{
	return m_state;
}

//��------------------------------------------------------------------��
//��*func�F�����蔻��
//��*arg�F��r����I�u�W�F�N�g
//��*return�Ftrue�i�������Ă���j�Afalse�i�������Ă��Ȃ��j
//��------------------------------------------------------------------��
//���˔���
bool Fragment::Collision(ObjectBase* A)
{
	float x1 = m_posX + m_grpW / 2;
	float y1 = m_posY + m_grpH / 2;
	float x2 = A->GetPosX() + A->GetGrpW() / 2;
	float y2 = A->GetPosY() + A->GetGrpH() / 2;
	float r1 = m_grpW / 2;
	float r2 = A->GetGrpW() / 2;

	//�~�̂����蔻��
	if ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) <= (r1 + r2)*(r1 + r2))
	{
		//���Ђ��ʏ��ԂȂ瓖�����Ă���
		if (m_state == FRAGMENT_NORMAL)
		{
			m_state = FRAGMENT_CATCH;
			return true;
		}
	}
	return false;
}


