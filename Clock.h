//**********************************//
//*	名　前：Clock.h
//*	内　容：時計クラス
//*	日　付：2017.5.2
//*	制作者：N.Shibayama
//**********************************//

#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

class Clock :public ObjectBase
{
protected:
	bool m_hand;									//時計の針(長針(true)、短針(false))
	DirectX::SimpleMath::Vector2 m_longTipPos;		//長針の先端座標
	DirectX::SimpleMath::Vector2 m_shortTipPos;		//短針の先端座標

public:
	Clock();
	~Clock();
	void Update();									//更新
	void Render();									//描画

	bool getHand();										//針の状態取得
	DirectX::SimpleMath::Vector2 getOrigin();			//長針の原点座標取得
	DirectX::SimpleMath::Vector2 getLongTipPos();		//針の先端座標取得
	DirectX::SimpleMath::Vector2 getShortTipPos();		//針の先端座標取得
	void clockwise();									//針を右回りに動かす
	//float calAngle(DirectX::SimpleMath::Vector2 origin,
	//	DirectX::SimpleMath::Vector2 longTip,
	//	DirectX::SimpleMath::Vector2 shortTip);			//3点の座標からなす角)の計算

	//デバック用数値
	void DrawNum(float x, float y, int n);


private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	//	テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clockTex;	//時計
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_LongTipTex;	//長針
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShortTipTex;	//短針
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_OriginTex;	//原点

	//	表示座標
	DirectX::SimpleMath::Vector2 m_screenPos;	//時計原点

	//	テクスチャ原点
	DirectX::SimpleMath::Vector2 m_origin;		//時計
	DirectX::SimpleMath::Vector2 m_longTOri;	//長針
	DirectX::SimpleMath::Vector2 m_shortTOri;	//短針
	DirectX::SimpleMath::Vector2 m_ori;			//原点

	//	回転
	float m_rotLongPos;		//長針回転
	float m_rotShortPos;	//短針回転
	//	座標角度
//	float m_LTPos;		//長針座標角度
//	float m_STPos;		//短針座標角度

	//デバック用
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_time_tex;	//通常時テクスチャ



};