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
	void Update();
	void Render();

	void Outdoor();		//画面内に欠片があるかどうか

	int State();		//欠片の状態取得

	bool Collision(ObjectBase * A);		//当たり判定

	float Angle(DirectX::SimpleMath::Vector2 tip_origin);				//欠片のある角度

	void AttackTip();		//針と当たった際に針と同じ方向に動く処理


private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fragment_tex;	//通常時テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_fragment_catch_tex;	//キャッチ後テクスチャ


	float m_fragmentLongAngle;		//角度（長針との当たり判定用
	float m_fragmentShortAngle;		//角度（短針との当たり判定用

	bool m_effect_state;

};
