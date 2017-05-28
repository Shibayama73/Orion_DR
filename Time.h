//∞----------------------------------------------------∞
//∞*ファイル名：Time.cpp								∞
//∞*内容　　　：時間クラス								∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.25 							∞
//∞----------------------------------------------------∞
#pragma once
#include "ObjectBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"
class Time : public ObjectBase
{
public:
	Time();
	~Time();
	void Render();
	//*今の時間をカウントする(-1した値が正値）
	void CurrentTime();
	//残りの時間の計算、falseになったらゲームオーバー
	bool RemnantTime();

	void DrawNum(float x, float y, int n);			//*数字の描画関数

private:
	int	m_current_time;		//*現在の時間
	int m_remnant_time;		//*残りの時間

	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_time_tex;	//通常時テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_remaining_tex;	//通常時テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_h_tex;	//通常時テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_now_tex;	//通常時テクスチャ


};

