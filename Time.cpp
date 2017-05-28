//��----------------------------------------------------��
//��*�t�@�C�����FTime.cpp								��
//��*���e�@�@�@�F���ԃN���X								��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.25 							��
//��----------------------------------------------------��

#include "pch.h"
#include "Time.h"

#include "GameMain.h"
#include <d3d11.h>

#include "Direct3D.h"
#include "DirectXTK.h"
#include <SimpleMath.h>

#include "Game.h"
#include "pch.h"
#include <Windows.h>
#include <Windef.h>
#include <WICTextureLoader.h>



using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace std;

//��������
const int TIME_MAX = 72;


//��------------------------------------------------------------------��
//��*func�F�R���X�g���N�^
//��*arg�F�Ȃ�
//��------------------------------------------------------------------��
Time::Time()
{
	//���l�̏�����
	//m_current_time = 0;
	m_current_time = 70;

	m_remnant_time = 10;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 26.0f;
	m_grpH = 32.0f;
	m_posX = 0.0f;
	m_posY = 0.0f;

	//�`��p
	m_deviceResources = Game::m_deviceResources.get();
	m_spriteBatch = Game::m_spriteBatch.get();

	//�ʏ펞�摜
	ComPtr<ID3D11Resource> time_resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/number2.png",
			time_resource.GetAddressOf(),
			m_time_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/remaining.png",
			time_resource.GetAddressOf(),
			m_remaining_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/time.png",
			time_resource.GetAddressOf(),
			m_h_tex.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/now.png",
			time_resource.GetAddressOf(),
			m_now_tex.ReleaseAndGetAddressOf()));

	//	���\�[�X����w�i�̃e�N�X�`���Ɣ��f
	ComPtr<ID3D11Texture2D> time;
	DX::ThrowIfFailed(time_resource.As(&time));

	//	�e�N�X�`�����
	CD3D11_TEXTURE2D_DESC timeDesc;
	time->GetDesc(&timeDesc);

	//	�e�N�X�`�����_���摜�̒��S�ɂ���
	m_origin.x = float(timeDesc.Width / 2.0f);
	m_origin.y = float(timeDesc.Height / 2.0f);


}
Time::~Time()
{	
}


//��------------------------------------------------------------------��
//��*func�F�`��֐�
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Time::Render()
{
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�
	m_spriteBatch->Draw(m_remaining_tex.Get(), Vector2(100, 185), nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_now_tex.Get(), Vector2(100, 65), nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_h_tex.Get(), Vector2(180, 105), nullptr, Colors::White, 0.f, m_origin);
	m_spriteBatch->Draw(m_h_tex.Get(), Vector2(180, 225), nullptr, Colors::White, 0.f, m_origin);

	m_spriteBatch->End();

	//���݂̎��ԕ\��
	DrawNum(100, 90, m_current_time - 1);

	//�c��̎��ԕ\��
	DrawNum(100, 210, m_remnant_time);


}

//��------------------------------------------------------------------��
//��*func�F���݂̎��Ԃ̎擾
//��*arg�F�Ȃ�
//��*return�F�Ȃ�
//��*heed�F���j��pos(450,0)�ɂȂ�����Ăяo��
//��------------------------------------------------------------------��
void Time::CurrentTime()
{
	m_current_time++;
}

//��------------------------------------------------------------------��
//��*func�F�c��̎��Ԍv�Z�֐�
//��*arg�F�Ȃ�
//��*return�F�c�莞�Ԃ�����(true)���A�Ȃ���(false)
//��*heed�Ffalse��Ԃ�����A�e�͂Ȃ��Q�[���I�[�o
//��------------------------------------------------------------------��
bool Time::RemnantTime()
{
	if (m_remnant_time != 0)
	{
		//��������-���̎��Ԃ��c��̎��Ԃɂ���
		m_remnant_time = TIME_MAX - (m_current_time-1);
		if (m_remnant_time > TIME_MAX)
		{
			m_remnant_time = TIME_MAX;
		}
		return true;
	}
	else
	{
		return false;
	}
}

//��------------------------------------------------------------------��
//��*func�F���ԕ`��֐�
//��*arg�F�`��ʒu(float x�Afloat y)�A�`�悷�鐔�l(int n)
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void Time::DrawNum(float x, float y, int n)
{
	//�`��
	CommonStates m_states(m_deviceResources->GetD3DDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultiplied�ŕs�����̐ݒ�

	int w = n;		//��Ɨp
	int i = 0;		//������

	RECT rect;

	if (w < 0)
	{
		rect = { (LONG)m_grpX, (LONG)m_grpY,(LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };

		m_spriteBatch->Draw(m_time_tex.Get(), Vector2(x, y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

		//DrawRectGraph(x, y, 0, 48, 25, 32, g_PongImage, TRUE, FALSE);
	}

	else
	{
		while (w)
		{
			m_grpX = (w % 10) * m_grpW;
			rect = {(LONG)m_grpX, (LONG)m_grpY, (LONG)(m_grpX + m_grpW), (LONG)(m_grpY + m_grpH) };
			m_spriteBatch->Draw(m_time_tex.Get(), Vector2((x - i * m_grpW), y), &rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

			w = w / 10;
			i++;
		}
	}

	m_spriteBatch->End();
}
