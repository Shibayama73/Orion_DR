//**********************************//
//*	名　前：Gauge.h
//*	内　容：欠片計量ゲージクラス
//*	日　付：2017.05.24
//* 更新日：2017.06.02
//*	制作者：N.Shibayama
//**********************************//

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"
#include "Fragment.h"

class Gauge:public ObjectBase
{
public:
	Gauge();
	~Gauge();
	void Update();								//更新
	void Render();								//描画
	void addGradation(int state);				//ゲージを増やす
	int getGradation();							//ゲージの値取得

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	//	テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hourglassTex;	//砂時計
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_colorTex;		//ゲージ色

	//	テクスチャ原点
	DirectX::SimpleMath::Vector2 m_origin;				//砂時計
	DirectX::SimpleMath::Vector2 m_gradationOrigin;		//ゲージ色

	//	表示座標
	DirectX::SimpleMath::Vector2 m_screenPos;			//砂時計
	DirectX::SimpleMath::Vector2 m_gradationPos;		//ゲージ色

	//	ゲージの目盛り数値(グラデーション)
	int m_gradation;

};
