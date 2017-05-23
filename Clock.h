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
	DirectX::SimpleMath::Vector2 m_shotTipPos;		//短針の先端座標

public:
	Clock();
	~Clock();
	void Update();									//更新
	void Render();									//描画
	bool getHand();									//針の状態取得
	DirectX::SimpleMath::Vector2 getLongTipPos();	//針の先端座標取得
	DirectX::SimpleMath::Vector2 getShotTipPos();	//針の先端座標取得
	void clockwise();								//針を右回りに動かす

	DirectX::SimpleMath::Vector2 getLongTipOrigin();	//長針の原点座標取得


private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	//	テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clockTex;	//時計
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_LongTipTex;	//長針
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShortTipTex;	//短針
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_OriginTex;	//原点

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_longTPos;
	DirectX::SimpleMath::Vector2 m_origin;
	DirectX::SimpleMath::Vector2 m_longTOri;	//長針原点
	DirectX::SimpleMath::Vector2 m_shortTOri;	//短針原点

	DirectX::SimpleMath::Vector2 m_ori;


	float m_rotLongPos;		//長針回転
	float m_rotShortPos;	//短針回転
	float m_LTPos;		//長針座標角度
	float m_STPos;		//短針座標角度


};