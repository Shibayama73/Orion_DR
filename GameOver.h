//**********************************//
//*	���@�O�FGameOver.h
//*	���@�e�F�I�[�o�[�V�[��
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
#include "ADX2Le.h"

class GameOver :public GameBase
{
public:
	GameOver();			//	�R���X�g���N�^
	~GameOver();		//	�f�X�g���N�^
	int UpdateGame();	//	�f�[�^�̍X�V
	void RenderGame();	//	�`�悷��

	//�����`��
	void DrawNum(float x, float y, int n);
	//�t�@�C���ǂݏ���
	int FileIO(int io, int *score);
	//	�����L���O�f�[�^�t�@�C���ǂݏ���
	int RankingDataFileIO(int io);
	//	�f�[�^�����Ԃɕ��ׂ�
	void SetRanking();

private:
	float m_grpX;	//�摜��X���W
	float m_grpY;	//�摜��Y���W
	float m_grpW;	//�摜��W���W
	float m_grpH;	//�摜��H���W

	int m_score;


	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_time_tex;	//�ʏ펞�e�N�X�`��


	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	//����
	int m_rank[3];

};
