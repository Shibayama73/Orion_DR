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
	//*���̎��Ԃ��J�E���g����(-1�����l�����l�j
	void CurrentTime();
	//�c��̎��Ԃ̌v�Z�Afalse�ɂȂ�����Q�[���I�[�o�[
	bool RemnantTime();

	void DrawNum(float x, float y, int n);			//*�����̕`��֐�

private:
	int	m_current_time;		//*���݂̎���
	int m_remnant_time;		//*�c��̎���

	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_time_tex;	//�ʏ펞�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_remaining_tex;	//�ʏ펞�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_h_tex;	//�ʏ펞�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_now_tex;	//�ʏ펞�e�N�X�`��


};

