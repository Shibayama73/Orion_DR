//∞----------------------------------------------------∞
//∞*ファイル名：GameStory.h							∞
//∞*内容　　　：ストーリー解説シーン					∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.06.15								∞
//∞----------------------------------------------------∞
#pragma once
#include "GameBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"

class GameStory :
	public GameBase
{
public:
	GameStory();
	~GameStory();
	int UpdateGame();	//	データの更新
	void RenderGame();	//	描画する

private:
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture3;	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture4;	//テクスチャ

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	int m_page;

};

