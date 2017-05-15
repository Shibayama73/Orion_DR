//**********************************//
//*	GameClear.h
//*	クリアシーン
//*	2017.4.25
//*	N.Shibayama & Ayaka.Y
//**********************************//

#pragma once
#include "GameBase.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "DeviceResources.h"
#include <SpriteBatch.h>


class GameClear :public GameBase
{
public:
	GameClear();	//	コンストラクタ
	~GameClear();	//	デストラクタ
	int UpdateGame();	//	データの更新
	wchar_t* RenderGame();//	描画する

private:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//テクスチャ
	std::unique_ptr<DX::DeviceResources> m_deviceResources;
};
