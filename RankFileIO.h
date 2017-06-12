//**********************************//
//*	���@�O�FRankFileIO.h
//*	���@�e�F���ʃt�@�C���N���X
//*	���@�t�F2017.06.12
//* �X�V���F2017.06.12
//*	����ҁFN.Shibayama
//**********************************//

#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

class RankFileIO
{
public:
	RankFileIO();
	~RankFileIO();
	//	�`�悷��
	void Render();
	//�����`��
	void DrawNum(float posX, float posY, int num);
	//	�����L���O�f�[�^�t�@�C���ǂݏ���
	int RankingDataFileIO(int io);
	//	�f�[�^�����Ԃɕ��ׂ�
	void SetRanking();
	//	�t�@�C���f�[�^�l�ƃX�R�A�̒l�̍~���Ƀ\�[�g����
	void ArraySort(int score);

private:
	float m_grpX;	//�摜��X���W
	float m_grpY;	//�摜��Y���W
	float m_grpW;	//�摜��W���W
	float m_grpH;	//�摜��H���W


	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;		//�e�N�X�`��

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	//����
	int m_rank[3];

};
