//----------------------------------------------------
//*t@CผFWire.h									
//*เe@@@FC[								
//*ง์า@@FAyaka Yamanaka							
//*ง์๚@F2017.05.18								
//----------------------------------------------------
#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "DeviceResources.h"


class Wire
{
public:
	Wire();
	~Wire();

	void Render(float pos_y);

private:
	//`ๆ
	DX::DeviceResources* m_deviceResources;
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_origin;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_wire_tex;	//สํeNX`

};

