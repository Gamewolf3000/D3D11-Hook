#pragma once

#include <d3d11.h>
//#include <d3dx11.h>

class RenderTarget
{
	ID3D11Device*		mDevice;
	ID3D11DeviceContext* mContext;
	ID3D11Texture2D*	mTexture;
public:
	RenderTarget();
	~RenderTarget();
	
	bool Init(ID3D11Device* device, ID3D11DeviceContext* context, D3D11_TEXTURE2D_DESC initDesc);
	bool Init(ID3D11Device* device, ID3D11DeviceContext* context, int width, int height, DXGI_FORMAT format);
	void Release();
	ID3D11RenderTargetView* GetTargetView();
	ID3D11DepthStencilView* GetDepthView();
	ID3D11ShaderResourceView* GetResource();
	void SetTarget();
	void Clear(float r, float g, float b, float a);

	ID3D11Texture2D* GetTexture();

	float GetWidth();
	float GetHeight();
private:
	ID3D11RenderTargetView* view;
	ID3D11ShaderResourceView* resource;
	float width;
	float height;
};
