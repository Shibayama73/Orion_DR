//**********************************//
//*	GameClear.h
//*	�N���A�V�[��
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "DeviceResources.h"
#include <SpriteBatch.h>


class GameClear :public GameBase
{
public:
	GameClear();	//	�R���X�g���N�^
	~GameClear();	//	�f�X�g���N�^
	int UpdateGame();	//	�f�[�^�̍X�V
	wchar_t* RenderGame();//	�`�悷��

private:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//�e�N�X�`��
	std::unique_ptr<DX::DeviceResources> m_deviceResources;
};
