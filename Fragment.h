//∞----------------------------------------------------∞
//∞*ファイル名：Fragment.h								∞
//∞*内容　　　：欠片クラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.22 							∞
//∞----------------------------------------------------∞

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

enum
{
	FRAGMENT_NORMAL,
	FRAGMENT_CATCH,
	FRAGMENT_LOSS,
};

class Fragment :
	public ObjectBase
{
public:
	Fragment();
	~Fragment();
	void Update(DirectX::SimpleMath::Vector2 origin);
	void Render();

	void Outdoor();		//画面内に欠片があるかどうか

	int State();		//欠片の状態取得

	bool Collision(ObjectBase * A);		//当たり判定


public:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fragment_tex;	//通常時テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fragment_catch_tex;	//キャッチ後テクスチャ

};
