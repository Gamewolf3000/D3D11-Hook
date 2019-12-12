#include "Device3D.h"

#include <d3d11_1.h>

Device3D::Device3D()
	: mSwapChain(NULL), mRenderTargetView(NULL), mDepthStencil(NULL),
	mDepthStencilView(NULL), mDevice(NULL),	mDeviceContext(NULL)
{
	mBackbuffer = NULL;

	m_iWidth = 0;
	m_iHeight = 0;
}

Device3D::~Device3D()
{
	if(mDeviceContext)
		mDeviceContext->ClearState();



	SAFE_RELEASE(mSwapChain);
	SAFE_RELEASE(mBackbuffer);
	SAFE_RELEASE(mRenderTargetView);
	SAFE_RELEASE(mDepthStencil);
	SAFE_RELEASE(mDepthStencilView);
	SAFE_RELEASE(mDeviceContext);
	SAFE_RELEASE(mDevice);
}

D3D_FEATURE_LEVEL Device3D::GetHighestFeatureLevel()
{
	HRESULT hr;

	//get maximum feature level
	D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_10_0;

	hr = D3D11CreateDevice(	NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		NULL,
		&FeatureLevel,
		NULL
		);

	return FeatureLevel;
}

HRESULT Device3D::ClearScreen(float r, float g, float b, float a)
{
	HRESULT hr = S_OK;

	float ClearColor[4] = {r, g, b, a};
	mDeviceContext->ClearRenderTargetView( mRenderTargetView, ClearColor );
	mDeviceContext->ClearDepthStencilView( mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0, 0 );

	return hr;
}

HRESULT Device3D::PresentScreen()
{
	if(FAILED(mSwapChain->Present( 0, 0 )))
		return E_FAIL;

	return S_OK;
}

HRESULT Device3D::CreateTargetView()
{
	HRESULT hr = S_OK;

	if(mBackbuffer == NULL)
	{
		D3D11_TEXTURE2D_DESC Desc;
		Desc.Width              = GetWidth();
		Desc.Height             = GetHeight();
		Desc.MipLevels          = 1;
		Desc.ArraySize          = 1;
		Desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // _SRGB;
		Desc.SampleDesc.Count   = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.Usage              = D3D11_USAGE_DEFAULT;
		Desc.BindFlags          = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		Desc.CPUAccessFlags     = 0;
		Desc.MiscFlags          = D3D11_RESOURCE_MISC_SHARED;

		hr = mDevice->CreateTexture2D(&Desc, NULL, &mBackbuffer );
	}

	SAFE_RELEASE(mRenderTargetView);
	hr = mDevice->CreateRenderTargetView( mBackbuffer, NULL, &mRenderTargetView );
	
	if( FAILED(hr) )
		return hr;

	return hr;
}

HRESULT Device3D::CreateDevice(DEVICE_INIT_DATA data)
{
	HRESULT hr = S_OK;

	UINT DeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	DeviceFlags		|= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverType;

	D3D_DRIVER_TYPE driverTypes[] = 
	{
		//D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	const D3D_FEATURE_LEVEL pFeatureLevels[] = {D3D_FEATURE_LEVEL_11_0};

	D3D_FEATURE_LEVEL initiatedFeatureLevel;
	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(NULL,
								driverType,
								NULL,
								DeviceFlags,
								pFeatureLevels,
								ARRAYSIZE(pFeatureLevels),
								D3D11_SDK_VERSION,
								&mDevice,
								&initiatedFeatureLevel,
								&mDeviceContext);

		if(SUCCEEDED(hr))
			break;
	}

	return hr;
}

HRESULT Device3D::CreateSwapChain(DEVICE_INIT_DATA data)
{
	HRESULT hr = S_OK;

	IDXGIDevice2 * pDXGIDevice = nullptr;
	hr = mDevice->QueryInterface(__uuidof(IDXGIDevice2), (void **)&pDXGIDevice);
      
	IDXGIAdapter * pDXGIAdapter = nullptr;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

	IDXGIFactory2 * pIDXGIFactory = nullptr;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory2), (void **)&pIDXGIFactory);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = m_iWidth;
	sd.BufferDesc.Height = m_iHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //_SRGB;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = data.Hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = data.Windowed;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	hr = pIDXGIFactory->CreateSwapChain(mDevice, &sd, &mSwapChain);

	if(SUCCEEDED(hr))
	{
		hr = mSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&mBackbuffer );
		if( FAILED(hr) )
			return hr;
	}

	SAFE_RELEASE(pIDXGIFactory);
	SAFE_RELEASE(pDXGIAdapter);
	SAFE_RELEASE(pDXGIDevice);
	return hr;
}

HRESULT Device3D::Initiate(DEVICE_INIT_DATA data)
{
	HRESULT hr = S_OK;;
	
	m_iWidth = data.Width;
	m_iHeight = data.Height;

	if(FAILED(hr = CreateDevice(data)))
		return hr;

	if(data.Hwnd != 0)
		CreateSwapChain(data);

	if(FAILED(hr = CreateTargetView()))
		return hr;

	if(FAILED(hr = CreateDepthStencilView()))
		return hr;

	ResetTargets();

	// Setup the viewport
	SetViewport();

	return hr;
}

void Device3D::ResetTargets()
{
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
}

HRESULT Device3D::Resize(INT32 Width, INT32 Height)
{
	HRESULT hr = S_OK;

	m_iWidth = Width;
	m_iHeight = Height;

	/*
	SAFE_RELEASE(mTexture2D);
	SAFE_RELEASE(mRenderTargetView);
	SAFE_RELEASE(mDepthStencilView);
	*/

	if(mRenderTargetView)
	{
		while(mRenderTargetView->Release());
		mRenderTargetView = NULL;
	}

	if(mDepthStencilView)
	{
		while(mDepthStencilView->Release());
		mDepthStencilView = NULL;
	}

	if(mSwapChain)
		hr = mSwapChain->ResizeBuffers(0, m_iWidth, m_iHeight, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

	if(FAILED(CreateTargetView()))
		return E_FAIL;

	if(FAILED(CreateDepthStencilView()))
		return E_FAIL;

	mDeviceContext->OMSetRenderTargets( 1, &mRenderTargetView, mDepthStencilView );

	SetViewport();

	return hr;
}

HRESULT Device3D::CreateDepthStencilView()
{
	HRESULT hr;

	// Create depth stencil texture and since we don't
	// need a stencil buffer we take 32-bits for depth buffer
	ID3D11Texture2D* pDepthStencil = NULL;
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = m_iWidth;
	descDepth.Height = m_iHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = mDevice->CreateTexture2D( &descDepth, NULL, &pDepthStencil );
	if( FAILED( hr ) )
	{
		MessageBox(NULL, _T("Unable to create depth texture."), _T("Starfield Error"), MB_ICONERROR | MB_OK);
		return hr;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;


	descDSV.Flags = 0;

	if( descDepth.SampleDesc.Count > 1 )
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	else
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = mDevice->CreateDepthStencilView( pDepthStencil, &descDSV, &mDepthStencilView );
	if( FAILED( hr ) )
	{
		MessageBox(NULL, _T("Unable to create depthstencil view."), _T("Starfield Error"), MB_ICONERROR | MB_OK);
		return hr;
	}

	//SAFE_RELEASE(pDepthStencil);
	if(pDepthStencil)
	{
		while(pDepthStencil->Release());
		pDepthStencil = NULL;
	}

	return hr;
}

INT32 Device3D::GetWidth()
{
	return m_iWidth;
}

INT32 Device3D::GetHeight()
{
	return m_iHeight;
}

HWND Device3D::GetHWND()
{
	return m_hWnd;
}

void Device3D::SetViewport()
{
	D3D11_VIEWPORT vp;
	vp.Width		= (float)m_iWidth;
	vp.Height		= (float)m_iHeight;
	vp.MinDepth		= 0.0f;
	vp.MaxDepth		= 1.0f;
	vp.TopLeftX		= 0;
	vp.TopLeftY		= 0;
	mDeviceContext->RSSetViewports( 1, &vp );
}

ID3D11Device* Device3D::GetDevice()
{
	return mDevice;
}

ID3D11DeviceContext* Device3D::GetDeviceContext()
{
	return mDeviceContext;
}

ID3D11Texture2D* Device3D::GetRenderTarget()
{
	return mBackbuffer;
}

ID3D11RenderTargetView* Device3D::GetRenderTargetView()
{
	return mRenderTargetView;
}