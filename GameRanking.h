//**********************************//
//*	名　前：GameRanking.h
//*	内　容：ランキングシーン
//*	日　付：2017.06.12
//* 更新日：2017.06.12
//*	制作者：N.Shibayama
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
	GameRanking();		//	コンストラクタ
	~GameRanking();		//	デストラクタ
	int UpdateGame();	//	データの更新
	void RenderGame();	//	描画する

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backTexture;	//背景

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	//	順位ファイル
	RankFileIO* m_rankFileIO;

};
