//∞----------------------------------------------------∞
//∞*ファイル名：Screw.h								∞
//∞*内容　　　：ネジクラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.06.01								∞
//∞----------------------------------------------------∞

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

enum 
{
	SCREW_NORMAL,
	SCREW_LOSS,
};

class Screw :
	public ObjectBase
{

public:
	Screw();
	~Screw();
	void Update();
	void Render();

	void Outdoor();		//画面内に欠片があるかどうか

	bool Collision(ObjectBase * A);		//当たり判定

	int State();		//状態の確認

	void AttackTip();

public:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_screw_tex;	//通常時テクスチャ


};

