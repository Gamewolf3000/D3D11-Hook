#ifndef D3DMAIN_H
#define D3DMAIN_H

#define SafeReleaseD3D(x) if (x != NULL) { x->Release(); x = NULL; } // Safe release of D3D pointers

#include <d3d11_4.h>
#include <tchar.h>

typedef HRESULT(__stdcall *CreateDXGIFactoryType)(REFIID, void**);

#include <stdafx.h>
#include "DeviceOverride.h"
#include "DeviceContextOverride.h"
#include "SwapChainOverride.h"

class D3D11Main
{
private:

	const unsigned int WIDTH = 1280;
	const unsigned int HEIGHT = 720;

	IDXGISwapChain1* swapChain = nullptr;
	ID3D11RenderTargetView* gBackbufferRTV = nullptr;

	ID3D11SamplerState* wrapSample;
	ID3D11BlendState* transparency;

	ID3D11Texture2D* gDepthStencilBuffer = NULL;
	ID3D11DepthStencilView* gDepthStencilView = NULL;

	D3D11_VIEWPORT vp;

	HWND wndHandle;

	HWND Init();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void SetViewport();

	void InitialiseStates();

public:

	D3D11Main();
	virtual ~D3D11Main();

	HWND GetWindow();
	void SwapBackBuffer();
	void Render();


};


D3D11Main::D3D11Main()
{
	wndHandle = Init();

	SetViewport();

	InitialiseStates();

	ShowWindow(wndHandle, SW_SHOWNORMAL);
}


D3D11Main::~D3D11Main()
{

	SafeReleaseD3D(gBackbufferRTV);
	SafeReleaseD3D(swapChain);

	SafeReleaseD3D(gDepthStencilBuffer);
	SafeReleaseD3D(gDepthStencilView);

	DestroyWindow(wndHandle);

}

HWND D3D11Main::Init()
{
	HRESULT hr = S_OK;
	HWND hwnd;
	HMODULE hDXGI = GetModuleHandle(_T("DXGI.DLL")); // Get handle to the dll?

	while (::GetModuleHandle(_T("D3D11.DLL")) == nullptr);

	DeviceOverride::GetInstance()->Init();
	DeviceContextOverride::GetInstance()->Init();

	while (::GetModuleHandle(_T("DXGI.DLL")) == nullptr);

	SwapChainOverride::GetInstance()->Init();


	if (hDXGI != NULL)
	{
		CreateDXGIFactoryType pCreateDXGIFactory = reinterpret_cast<CreateDXGIFactoryType>(GetProcAddress(hDXGI, "CreateDXGIFactory")); // Fetch the adress of the factory creator?

		if (pCreateDXGIFactory)
		{
			IDXGIFactory2* pFactory;
			hr = pCreateDXGIFactory(__uuidof(IDXGIFactory2), (void**)(&pFactory)); // Use the factory creator to create a factory

			if (pFactory)
			{
				HMODULE hD3D = nullptr;
				IUnknown* d3d_device = nullptr;

				if (hD3D = GetModuleHandle(_T("D3D11.DLL"))) // D3D11
				{
					typedef HRESULT(__stdcall *D3D11CreateDeviceType)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL*, UINT, UINT, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**); // Function to create the device and the devicecontext?

					D3D11CreateDeviceType pD3D11CreateDevice = reinterpret_cast<D3D11CreateDeviceType>(GetProcAddress(hD3D, "D3D11CreateDevice")); // Get the factory adress of what we just typdefed?

					ID3D11DeviceContext* d3d_device_context11 = nullptr;
					const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0 };
					D3D_FEATURE_LEVEL initiated_feature_level;
					pD3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, feature_levels, 1, D3D11_SDK_VERSION, (ID3D11Device**)&d3d_device, &initiated_feature_level, &d3d_device_context11); // Use the function to create the device and device context
					SAFE_RELEASE(d3d_device_context11);
				}

				hwnd = CreateWindowW(L"STATIC", L"D3D11 Hooker", WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, 0,
					NULL, NULL, 0); // Create the window

				DXGI_SWAP_CHAIN_DESC1 desc;
				ZeroMemory(&desc, sizeof(desc));

				RECT rcWnd;
				GetClientRect(hwnd, &rcWnd);
				desc.Width = rcWnd.right - rcWnd.left;
				desc.Height = rcWnd.bottom - rcWnd.top;
				desc.Stereo = FALSE;
				desc.Flags = 0;
				desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;

				desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				desc.BufferCount = 2;

				desc.Scaling = DXGI_SCALING_STRETCH; //this is the implicit behavior of DXGI when you call the IDXGIFactory::CreateSwapChain method.


				if (SUCCEEDED(pFactory->CreateSwapChainForHwnd(
					DeviceOverride::GetInstance()->GetDevice(),
					hwnd,
					&desc,
					nullptr,
					nullptr,
					&swapChain))) // Create the swap chain
				{
					// get the address of the back buffer
					ID3D11Texture2D* pBackBuffer = nullptr;
					swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

					// use the back buffer address to create the render target

					DeviceOverride::GetInstance()->GetDevice()->CreateRenderTargetView(pBackBuffer, NULL, &gBackbufferRTV);


					pBackBuffer->Release();

					D3D11_TEXTURE2D_DESC depthStencilDesc; // Create DepthStencil
					depthStencilDesc.Width = WIDTH;
					depthStencilDesc.Height = HEIGHT;
					depthStencilDesc.MipLevels = 1;
					depthStencilDesc.ArraySize = 1;
					depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
					depthStencilDesc.SampleDesc.Count = 1;
					depthStencilDesc.SampleDesc.Quality = 0;
					depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
					depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
					depthStencilDesc.CPUAccessFlags = 0;
					depthStencilDesc.MiscFlags = 0;

					DeviceOverride::GetInstance()->GetDevice()->CreateTexture2D(&depthStencilDesc, 0, &gDepthStencilBuffer);
					DeviceOverride::GetInstance()->GetDevice()->CreateDepthStencilView(gDepthStencilBuffer, 0, &gDepthStencilView);

					// set the render target as the back buffer
					DeviceContextOverride::GetInstance()->GetDeviceContext()->OMSetRenderTargets(1, &gBackbufferRTV, gDepthStencilView);
				}

				//SAFE_RELEASE(swap_chain1);
				//SAFE_RELEASE(d3d_device);
				SafeReleaseD3D(pFactory);
				//DestroyWindow(hwnd);
			}
		}
	}

	return hwnd;
}

LRESULT CALLBACK D3D11Main::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void D3D11Main::SetViewport()
{
	//D3D11_VIEWPORT vp;
	vp.Width = (float)WIDTH;
	vp.Height = (float)HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
}

HWND D3D11Main::GetWindow()
{
	return wndHandle;
}

void D3D11Main::SwapBackBuffer()
{
	swapChain->Present(0, 0);
}

void D3D11Main::InitialiseStates()
{
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DeviceOverride::GetInstance()->GetDevice()->CreateSamplerState(&samplerDesc, &wrapSample);

	DeviceContextOverride::GetInstance()->GetDeviceContext()->VSSetSamplers(0, 1, &wrapSample);
	DeviceContextOverride::GetInstance()->GetDeviceContext()->PSSetSamplers(0, 1, &wrapSample);

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_BLEND_DESC transparentDesc;
	transparentDesc.AlphaToCoverageEnable = false;
	transparentDesc.IndependentBlendEnable = false;

	transparentDesc.RenderTarget[0].BlendEnable = true;
	transparentDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	transparentDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	transparentDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	transparentDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	transparentDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DeviceOverride::GetInstance()->GetDevice()->CreateBlendState(&transparentDesc, &transparency);

	DeviceContextOverride::GetInstance()->GetDeviceContext()->OMSetBlendState(transparency, NULL, 0xffffffff);

}

void D3D11Main::Render()
{
	//DeviceContextOverride::GetInstance()->GetDeviceContext()->OMSetBlendState(transparency, NULL, 0xffffffff);
	//DeviceContextOverride::GetInstance()->GetDeviceContext()->RSSetState(nullptr);
	//DeviceContextOverride::GetInstance()->GetDeviceContext()->OMSetDepthStencilState(nullptr, 0);

	//DeviceContextOverride::GetInstance()->GetDeviceContext()->VSSetSamplers(0, 1, &wrapSample);
	//DeviceContextOverride::GetInstance()->GetDeviceContext()->PSSetSamplers(0, 1, &wrapSample);

	//DeviceContextOverride::GetInstance()->GetDeviceContext()->OMSetRenderTargets(1, &gBackbufferRTV, gDepthStencilView);

	float clearColor[] = { 0, 0, 1, 1 };
	DeviceContextOverride::GetInstance()->GetDeviceContext()->RSSetViewports(1, &vp);
	DeviceContextOverride::GetInstance()->GetDeviceContext()->ClearRenderTargetView(gBackbufferRTV, clearColor);
	DeviceContextOverride::GetInstance()->GetDeviceContext()->ClearDepthStencilView(gDepthStencilView, D3D11_CLEAR_DEPTH, 1.0, 0);

}






#endif