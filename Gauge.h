//**********************************//
//*	名　前：Gauge.h
//*	内　容：欠片計量ゲージクラス
//*	日　付：2017.5.24
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
	void Update();									//更新
	void Render();									//描画
	void addGradation(int state);				//ゲージを増やす

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	//	テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bottleTex;	//瓶
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_colorTex;	//欠片色

	//	テクスチャ原点
	DirectX::SimpleMath::Vector2 m_origin;
	DirectX::SimpleMath::Vector2 m_gradationOrigin;
	//	表示座標
	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_gradationPos;

	//	ゲージの目盛り数(グラデーション)
	int m_gradation;

};
