#ifndef DEVICE_3D__H
#define DEVICE_3D__H

#include <stdafx.h>

struct DEVICE_INIT_DATA
{
	HWND Hwnd;
	INT32 Width;
	INT32 Height;
	BOOL Windowed;
};

class Device3D
{
protected:
	//Direct3D device pointers
	IDXGISwapChain*				mSwapChain;
	ID3D11RenderTargetView*		mRenderTargetView;
	ID3D11Texture2D*			mDepthStencil;
	ID3D11DepthStencilView*		mDepthStencilView;
	ID3D11Device*				mDevice;
	ID3D11DeviceContext*		mDeviceContext;

	//texture pointer used by Direc3D9Ex and Direct2D devices
	ID3D11Texture2D*			mBackbuffer;

	//backbuffer dimensions
	INT32	m_iWidth;
	INT32	m_iHeight;
	HWND	m_hWnd;

protected:

	D3D_FEATURE_LEVEL GetHighestFeatureLevel();
	HRESULT CreateTargetView();
	HRESULT CreateDepthStencilView();
	void SetViewport();

	HRESULT CreateDevice(DEVICE_INIT_DATA data);
	HRESULT CreateSwapChain(DEVICE_INIT_DATA data);

public:
	Device3D();
	~Device3D();
	HRESULT Initiate(DEVICE_INIT_DATA data);
	HRESULT Resize(INT32 Width, INT32 Height);

	HRESULT ClearScreen(float r, float g, float b, float a);
	HRESULT PresentScreen();

	INT32 GetWidth();
	INT32 GetHeight();
	HWND GetHWND();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	ID3D11Texture2D* GetRenderTarget();
	ID3D11RenderTargetView* GetRenderTargetView();

	void ResetTargets();
};

#endif
