//**********************************//
//*	名　前：RankFileIO.h
//*	内　容：順位ファイルクラス
//*	日　付：2017.06.12
//* 更新日：2017.06.12
//*	制作者：N.Shibayama
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
	//	描画する
	void Render();
	//数字描画
	void DrawNum(float posX, float posY, int num);
	//	ランキングデータファイル読み書き
	int RankingDataFileIO(int io);
	//	データを順番に並べる
	void SetRanking();
	//	ファイルデータ値とスコアの値の降順にソートする
	void ArraySort(int score);

private:
	float m_grpX;	//画像のX座標
	float m_grpY;	//画像のY座標
	float m_grpW;	//画像のW座標
	float m_grpH;	//画像のH座標


	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;		//テクスチャ

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	//順位
	int m_rank[3];

};
