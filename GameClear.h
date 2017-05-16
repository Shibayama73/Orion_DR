//**********************************//
//*	GameClear.h
//*	クリアシーン
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
	GameClear();		//	コンストラクタ
	~GameClear();		//	デストラクタ
	int UpdateGame();	//	データの更新
	void RenderGame();	//	描画する

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//テクスチャ

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

};
