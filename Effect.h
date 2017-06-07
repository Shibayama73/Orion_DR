//∞----------------------------------------------------∞
//∞*ファイル名：Effect.h								∞
//∞*内容　　　：エフェクトクラス						∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.06.05								∞
//∞----------------------------------------------------∞

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"


	enum
	{
		EFFECT_OFF,
		EFFECT_ON,
		EFFECT_LOSS,
	};
class Effect : public ObjectBase
{
public:
	Effect();
	~Effect();
	void Update();
	void Render();
	void ChengeState(float posX, float posY);
	void EffectLoss();
	int State();

private:
	//描画
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_effect_tex;	//エフェクト用テクスチャ

	int cnt;

};

