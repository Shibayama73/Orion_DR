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
	m_posX = rand() % 700;
	m_posY = (rand() % -100) - 100;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpW = 32;
	m_grpH = 32;

	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�ʏ펞�摜
	ComPtr<ID3D11Resource> fragment_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/fragment.png",
			fragment_resource.GetAddressOf(),
			m_fragment_tex.ReleaseAndGetAddressOf()));

	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> fragment;
	DX::ThrowIfFailed(fragment_resource.As(&fragment));

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
void Fragment::Update()
{
	m_spdY += 0.1;
	m_posY += m_spdY;
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

	m_spriteBatch->Draw(m_fragment_tex.Get(), Vector2(m_posX, m_posY), nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();

}

//��------------------------------------------------------------------��
//��*func�F��ʓ��Ɍ��Ђ����邩�ǂ���
//��*arg�F�Ȃ�
//��*return�Ftrue�i����j�Afalse�i�Ȃ��j
//��------------------------------------------------------------------��
bool Fragment::Outdoor()
{
	if (m_posY > 640)
	{
		return false;
	}
	return true;
}
