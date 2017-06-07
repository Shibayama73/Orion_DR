//��----------------------------------------------------��
//��*�t�@�C�����FScrew.cpp								��
//��*���e�@�@�@�F�l�W�N���X								��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.06.01								��
//��----------------------------------------------------��


#include "pch.h"
#include "Screw.h"

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

Screw::Screw()
{
	m_posX = rand() % 470 + 200;
	m_posY = (rand() % -1000) - 1010;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpW = 64;
	m_grpH = 64;



	m_state = SCREW_NORMAL;

	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�ʏ펞�摜
	ComPtr<ID3D11Resource> screw_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/bolt.png",
			screw_resource.GetAddressOf(),
			m_screw_tex.ReleaseAndGetAddressOf()));

	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> screw;
	DX::ThrowIfFailed(screw_resource.As(&screw));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC screwDesc;
	screw->GetDesc(&screwDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(screwDesc.Width / 2.0f);
	m_origin.y = float(screwDesc.Height / 2.0f);

}

//��------------------------------------------------------------------��
//��*func�F�f�X�g���N�^
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
Screw::~Screw()
{
}

//��------------------------------------------------------------------��
//��*func�F�X�V����
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Screw::Update()
{
	m_spdY += 0.02;
	m_posY += m_spdY;
	m_posX += m_spdX;


	//��O�ɏo�Ă��邩�̔���
	Outdoor();
}

//��------------------------------------------------------------------��
//��*func�F�`�揈��
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Screw::Render()
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	m_spriteBatch->Draw(m_screw_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);


	m_spriteBatch->End();

}

//��------------------------------------------------------------------��
//��*func�F��ʓ��Ɍ��Ђ����邩�ǂ���
//��*arg�F�Ȃ�
//��*return�Ftrue�i����j�Afalse�i�Ȃ��j
//��------------------------------------------------------------------��
void Screw::Outdoor()
{
	if (m_posY + m_grpH > 700)
	{
		m_state = SCREW_LOSS;
	}

}

//��------------------------------------------------------------------��
//��*func�F�����蔻��
//��*arg�F��r����I�u�W�F�N�g
//��*return�Ftrue�i�������Ă���j�Afalse�i�������Ă��Ȃ��j
//��------------------------------------------------------------------��
//���˔���
bool Screw::Collision(ObjectBase* A)
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
		m_state = SCREW_LOSS;
		return true;
	}
	return false;
}

//��------------------------------------------------------------------��
//��*func�F��Ԃ��擾����
//��*arg�F�Ȃ�
//��*return�Fm_state
//��------------------------------------------------------------------��
int Screw::State()
{
	return m_state;
}
