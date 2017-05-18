//**********************************//
//*	GamePlay.h
//*	プレイシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

#include "Clock.h"
#include "Player.h"
#include "Wire.h"



class GamePlay :public GameBase
{
public:
	GamePlay();			//	コンストラクタ
	~GamePlay();		//	デストラクタ
	int UpdateGame();	//	データの更新
	void RenderGame();	//	描画する

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//テクスチャ

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	Clock* m_clock;		//時計
	Player* m_player;	//プレイヤー
	Wire* m_wire;		//ワイヤー


};
