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
#include <WICTextureLoader.h>



using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace std;

//��������
const int TIME_MAX = 72;


Time::Time()
{
	//���l�̏�����
	m_current_time = 0;
	m_remnant_time = 0;
	m_spdX = 0.0f;
	m_spdY = 0.0f;
	m_grpX = 0.0f;
	m_grpY = 0.0f;
	m_grpW = 0.0f;
	m_grpH = 0.0f;
	m_posX = 0.0f;
	m_posY = 0.0f;
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
	if (m_remnant_time < TIME_MAX)
	{
		m_remnant_time = TIME_MAX - m_current_time;
		return true;
	}
	return false;
}

//��------------------------------------------------------------------��
//��*func�F���ԕ`��֐�
//��*arg�F�`��ʒu(float x�Afloat y)�A�`�悷�鐔�l(int n)
//��*return�F�Ȃ�
//��------------------------------------------------------------------��
void DrawNum(float x, float y, int n)
{
	int w = n;		//��Ɨp
	int i = 0;		//������

	if (w == 0)
	{
		//DrawRectGraph(x, y, 0, 48, 25, 32, g_PongImage, TRUE, FALSE);
	}

	else
	{
		while (w)
		{
			//DrawRectGraph(x - i * 25, y, (w % 10) * 25, 48, 25, 32, g_PongImage, TRUE, FALSE);
			w = w / 10;
			i++;
		}
	}
}
