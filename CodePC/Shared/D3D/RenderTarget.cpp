#include "RenderTarget.h"

RenderTarget::RenderTarget()
{
	mDevice = NULL;
	mContext = NULL;
	mTexture = NULL;
}

RenderTarget::~RenderTarget()
{
	Release();
}

bool RenderTarget::Init(ID3D11Device* device, ID3D11DeviceContext* context, D3D11_TEXTURE2D_DESC initDesc)
{
	mDevice = device;
	mContext = context;

	HRESULT hr = mDevice->CreateTexture2D(&initDesc, NULL, &mTexture);

	if(hr != S_OK)
		return false;

	//create render target view from texture
	D3D11_RENDER_TARGET_VIEW_DESC DescRT;
	DescRT.Format = initDesc.Format;
	DescRT.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	DescRT.Texture2DArray.MipSlice = 0;

	hr = mDevice->CreateRenderTargetView( mTexture, &DescRT, &view);
	
	
	if(hr != S_OK)
	{
		mTexture->Release();
		return false;
	}

	// Create the shader-resource view from the texture
	D3D11_SHADER_RESOURCE_VIEW_DESC srDesc;
	srDesc.Format = initDesc.Format;
	srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
	srDesc.Texture2D.MipLevels = 1;

	hr = mDevice->CreateShaderResourceView( mTexture, &srDesc, &resource );

	mTexture->Release();

	if(hr != S_OK)
	{
		view->Release();
		return false;
	}
	
	this->width = (float)initDesc.Width;
	this->height = (float)initDesc.Height;
	return true;	
}

bool RenderTarget::Init(ID3D11Device* device, ID3D11DeviceContext* context, int width, int height, DXGI_FORMAT format)
{
	//create render target texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	return Init(device, context, desc);
}

ID3D11Texture2D* RenderTarget::GetTexture()
{
	return mTexture;
}

void RenderTarget::Release()
{
	if(this->view)
	{
		view->Release();
	}

	if(resource)
	{
		resource->Release();
	}

	if(mTexture)
	{
		mTexture->Release();
	}
}

ID3D11RenderTargetView* RenderTarget::GetTargetView()
{
	return view;
}

ID3D11ShaderResourceView* RenderTarget::GetResource()
{
	return resource;
}

void RenderTarget::SetTarget()
{
	//set the targets
	mContext->OMSetRenderTargets( 1, &this->view, NULL);

    D3D11_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    mContext->RSSetViewports( 1, &vp );
}

void RenderTarget::Clear(float r, float g, float b, float a)
{
	float ClearColor[4] = {r, g, b, a};
	mContext->ClearRenderTargetView(this->view, ClearColor);
}

float RenderTarget::GetWidth()
{
	return width;
}

float RenderTarget::GetHeight()
{
	return height;
}