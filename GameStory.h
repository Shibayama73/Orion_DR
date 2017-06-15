//��----------------------------------------------------��
//��*�t�@�C�����FGameStory.h							��
//��*���e�@�@�@�F�X�g�[���[����V�[��					��
//��*����ҁ@�@�FAyaka Yamanaka							��
//��*��������@�F2017.06.15								��
//��----------------------------------------------------��
#pragma once
#include "GameBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

class GameStory :
	public GameBase
{
public:
	GameStory();
	~GameStory();
	int UpdateGame();	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture3;	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture4;	//�e�N�X�`��

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	int m_page;

};

