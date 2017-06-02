//**********************************//
//*	���@�O�FGameLogo.h
//*	���@�e�F���S�V�[��
//*	���@�t�F2017.04.25
//* �X�V���F2017.06.02
//*	����ҁFN.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

class GameLogo :public GameBase
{
public:
	GameLogo();			//	�R���X�g���N�^
	~GameLogo();		//	�f�X�g���N�^
	int UpdateGame();	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bkackTexture;	//�e�N�X�`��

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	float m_fadeCount;

};
