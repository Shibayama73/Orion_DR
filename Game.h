//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "GameMain.h"
#include "GamePlay.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

	// Device resources.
	static std::unique_ptr<DX::DeviceResources> m_deviceResources;
	static std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;


private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

//	GameMain* m_gamemain;
//	std::unique_ptr<DirectX::SpriteFont> m_font;

	DirectX::SimpleMath::Vector2 m_fontPos;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	//テクスチャ

	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;

	//	デバッグ用============
	GameMain* m_gameMain;
	GamePlay* m_gamePlay;


};
