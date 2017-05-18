//∞----------------------------------------------------∞
//∞*ファイル名：Wire.h									∞
//∞*内容　　　：ワイヤー								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.18								∞
//∞----------------------------------------------------∞
#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"


class Wire
{
public:
	Wire();
	~Wire();

	void Render(float pos_y);

private:
	//描画
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_wire_tex;	//通常時テクスチャ

};

