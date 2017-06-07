//**********************************//
//*	名　前：GameOver.h
//*	内　容：オーバーシーン
//*	日　付：2017.04.25
//* 更新日：2017.06.02
//*	制作者：N.Shibayama & Ayaka.Y
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
	GameOver();			//	コンストラクタ
	~GameOver();		//	デストラクタ
	int UpdateGame();	//	データの更新
	void RenderGame();	//	描画する

	//数字描画
	void DrawNum(float x, float y, int n);
	//ファイル読み書き
	int FileIO(int io, int *score);
	//	ランキングデータファイル読み書き
	int RankingDataFileIO(int io);
	//	データを順番に並べる
	void SetRanking();

private:
	float m_grpX;	//画像のX座標
	float m_grpY;	//画像のY座標
	float m_grpW;	//画像のW座標
	float m_grpH;	//画像のH座標

	int m_score;


	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_time_tex;	//通常時テクスチャ


	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	//順位
	int m_rank[3];

};
