//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Direct3D.h"
#include "DirectXTK.h"

#include "GameMain.h"

#include <WICTextureLoader.h>

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

std::unique_ptr<DX::DeviceResources> Game::m_deviceResources;
std::unique_ptr<DirectX::SpriteBatch> Game::m_spriteBatch;

Game::Game()
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);

}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	////	追加部分=================================================================================
	////	リソース生成
	//m_spriteBatch = std::make_unique<SpriteBatch>(m_deviceResources->GetD3DDeviceContext());
	//
	////	リソース読み込み
	//ComPtr<ID3D11Resource> resource;
	//DX::ThrowIfFailed(
	//	CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resouces/clock.png", resource.GetAddressOf(),
	//		m_texture.ReleaseAndGetAddressOf()));

	////	リソースから猫のテクスチャと判断
	//ComPtr<ID3D11Texture2D> clock;
	//DX::ThrowIfFailed(resource.As(&clock));

	////	テクスチャ情報
	//CD3D11_TEXTURE2D_DESC clockDesc;
	//clock->GetDesc(&clockDesc);

	////	テクスチャ原点を画像の中心にする
	//m_origin.x = float(clockDesc.Width / 2.0f);
	//m_origin.y = float(clockDesc.Height / 2.0f);

	////	表示座標を画面中央に指定
	//m_screenPos.x = m_deviceResources->GetOutputSize().right / 2.0f;
	//m_screenPos.y = m_deviceResources->GetOutputSize().bottom / 2.0f;


	////==========================================================================================


	//	追加してエラー
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_deviceResources->GetD3DDeviceContext());


	//	デバッグ用
	m_gameMain = new GameMain();
	//m_gamePlay = new GamePlay();

	//キーボードの初期化
	//keyboard = std::make_unique<Keyboard>();

}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
	DirectXTK_UpdateInputState();

	//	デバッグ用=========
	m_gameMain->Scene();
	//m_gamePlay->UpdateGame();

    elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.


//	//	追加部分=================================================================================
//	//	スプライトの描画
//	//m_spriteBatch->Begin();
//	CommonStates m_states(m_deviceResources->GetD3DDevice());
//	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states.NonPremultiplied());	//NonPremultipliedで不透明の設定
//	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.f, m_origin);
//
//	//const wchar_t* output = L"Hello World";
////	const wchar_t* output = m_gamemain->Output();
//
//	//Vector2 origin = m_font->MeasureString(output) / 2.f;
///*
//	m_font->DrawString(m_spriteBatch.get(), output,
//		Vector2(100, 100));
//*/
//	m_spriteBatch->End();
//	//==========================================================================================
//
	
//// キー入力やマウス情報の更新
//	DirectXTK_UpdateInputState();


	m_gameMain->m_base->RenderGame();
	//m_gamePlay->RenderGame();


    context;

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();


}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 700;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
