//**********************************//
//*	名　前：GameTitle.h
//*	内　容：タイトルシーン
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

class GameTitle :public GameBase
{
public:
	GameTitle();		//	コンストラクタ
	~GameTitle();		//	デストラクタ
	int UpdateGame();	//	データの更新
	void RenderGame();	//	描画する

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;	//テクスチャ

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

};
