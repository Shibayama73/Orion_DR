//**********************************//
//*	���@�O�FGameRanking.h
//*	���@�e�F�����L���O�V�[��
//*	���@�t�F2017.06.12
//* �X�V���F2017.06.12
//*	����ҁFN.Shibayama
//**********************************//

#pragma once
#include "GameBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"
#include "RankFileIO.h"

class GameRanking :public GameBase
{
public:
	GameRanking();		//	�R���X�g���N�^
	~GameRanking();		//	�f�X�g���N�^
	int UpdateGame();	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backTexture;	//�w�i

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	//	���ʃt�@�C��
	RankFileIO* m_rankFileIO;

};
