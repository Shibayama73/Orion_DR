//��----------------------------------------------------��
//��*�t�@�C�����FTime.cpp								��
//��*���e�@�@�@�F���ԃN���X								��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.05.25 							��
//��----------------------------------------------------��
#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"
class Time : public ObjectBase
{
public:
	Time();
	~Time();
	void Render();
	//*���̎��Ԃ��J�E���g����
	void CurrentTime();
	//�c��̎��Ԃ̌v�Z�Afalse�ɂȂ�����Q�[���I�[�o�[
	bool RemnantTime();

private:
	int	m_current_time;		//*���݂̎���
	int m_remnant_time;		//*�c��̎���
};

