//∞----------------------------------------------------∞
//∞*ファイル名：Wire.h									∞
//∞*内容　　　：ワイヤー								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.18								∞
//∞----------------------------------------------------∞
#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"


class Wire : public ObjectBase
{
public:
	Wire(float posX);
	~Wire();

	void Update(float pos_x);

	void Render(float pos_x);

	void Elimination();		//消滅させる

	bool State();		//表示情報の取得

private:
	//描画
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_wire_tex;	//通常時テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_wire_L_tex;	//通常時左テクスチャ

	bool m_state;		//表示されているか、非表示になっているか（true：表示、false：非表示）
	bool m_elimination; //消滅しているか否か
};

