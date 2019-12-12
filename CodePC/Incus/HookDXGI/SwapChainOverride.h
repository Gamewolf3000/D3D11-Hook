#pragma once

#include "GlobalData.h"

#include "DeviceContextOverride.h"

typedef HRESULT(__stdcall *CreateDXGIFactoryType)(REFIID, void**);
typedef HRESULT(__stdcall *D3D10CreateDeviceAndSwapChainType)(IDXGIAdapter*, D3D10_DRIVER_TYPE, HMODULE, UINT, UINT, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**, ID3D10Device**);

typedef HRESULT(__stdcall *IDXGIFactory_CreateSwapChainType)(IDXGIFactory*, IUnknown *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc, IDXGISwapChain **ppSwapChain);

typedef HRESULT(__stdcall *DXGI_SwapChain1_Present1Type)(IDXGISwapChain1 *, UINT, UINT, const DXGI_PRESENT_PARAMETERS *);
typedef HRESULT(__stdcall *DXGI_SwapChain_PresentType)(IDXGISwapChain *, UINT, UINT);
typedef HRESULT(__stdcall *DXGI_SwapChain_SetFullscreenStateType)(IDXGISwapChain *, BOOL, IDXGIOutput *);
typedef HRESULT(__stdcall *DXGI_SwapChain_GetFullscreenStateType)(IDXGISwapChain *, BOOL*, IDXGIOutput **);
typedef HRESULT(__stdcall *DXGI_SwapChain_ResizeTargetType)(IDXGISwapChain *, const DXGI_MODE_DESC *);
typedef HRESULT(__stdcall *DXGI_SwapChain_ResizeBuffersType)(IDXGISwapChain *, UINT, UINT, UINT, DXGI_FORMAT, UINT);

class SwapChainOverride
{
	static SwapChainOverride* instance_;

	IDXGISwapChain* swap_chain_;
	IDXGISwapChain1* swap_chain_1_;
	ID3D11DeviceContext* deviceContext;
	D3DResolve* d3d_resolve_;

	SwapChainOverride()
	{
		swap_chain_ = nullptr;
		swap_chain_1_ = nullptr;
	}

private:
	HardHook hook_Present_;
	HardHook hook_Present_1_;
	HardHook hook_SetFullscreenState_;
	HardHook hook_GetFullscreenState_;
	HardHook hook_ResizeBuffers_;
	HardHook hook_ResizeTarget_;
public:

	static SwapChainOverride* GetInstance();

	HRESULT Init(IDXGISwapChain1* swapChain)
	{
		this->swap_chain_1_ = swapChain;

		// Setup Hooks
		hook_Present_.SetupInterface(swap_chain_1_, 8, reinterpret_cast<voidFunc>(Present));
		hook_SetFullscreenState_.SetupInterface(swap_chain_1_, 10, reinterpret_cast<voidFunc>(SetFullscreenState));
		hook_GetFullscreenState_.SetupInterface(swap_chain_1_, 11, reinterpret_cast<voidFunc>(GetFullscreenState));
		hook_ResizeBuffers_.SetupInterface(swap_chain_1_, 13, reinterpret_cast<voidFunc>(ResizeBuffers));
		hook_ResizeTarget_.SetupInterface(swap_chain_1_, 14, reinterpret_cast<voidFunc>(ResizeTarget));
		hook_Present_1_.SetupInterface(swap_chain_1_, 22, reinterpret_cast<voidFunc>(Present1));

		//this->swap_chain_1_ = nullptr; // ???

		return S_OK;
	}

	IDXGIFactory2* GetDeviceFactory(IUnknown* pDevice)
	{
		IDXGIDevice*  dxgiDevice = nullptr;
		IDXGIFactory2* dxgiFactory = nullptr;
		IDXGIAdapter* dxgiAdapter = nullptr;

		HRESULT hr = pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice); // Fetch the device?
		if (SUCCEEDED(hr))
		{
			hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter); // Get an adapter to the interface?
			if (SUCCEEDED(hr))
			{
				hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory); // Get the factory that created the adapter?
			}
		}

		SAFE_RELEASE(dxgiAdapter);
		SAFE_RELEASE(dxgiDevice);

		return dxgiFactory; // Return the factory
	}

	HRESULT ValidateSwapChain1(IDXGISwapChain* swap_chain)
	{
		HRESULT hr = S_OK;

		if (swap_chain_ != swap_chain) // Check if it is not our swapchain
		{
			swap_chain_ = swap_chain; // if it is not ours, then make it ours

			SAFE_RELEASE(swap_chain_1_); // Release our other swap chain, but why?

			IDXGIDevice* dxgiDevice = nullptr;
			swap_chain_->GetDevice(__uuidof(IDXGIDevice), (void**)&dxgiDevice); // Get the device from the swap chain
			IDXGIFactory2* pDXGIFactory12 = GetDeviceFactory(dxgiDevice); // Get the factory that created the device?

			DXGI_SWAP_CHAIN_DESC sd;
			swap_chain->GetDesc(&sd);

			swap_chain_->SetFullscreenState(FALSE, NULL);

			HWND hwnd = sd.OutputWindow;
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
			swapChainDesc.SwapEffect = sd.SwapEffect;
			swapChainDesc.BufferCount = sd.BufferCount;
			swapChainDesc.BufferUsage = sd.BufferUsage;
			swapChainDesc.Flags = sd.Flags;
			swapChainDesc.Flags &= ~DXGI_PRESENT_RESTRICT_TO_OUTPUT;
			swapChainDesc.Format = sd.BufferDesc.Format;
			swapChainDesc.Width = sd.BufferDesc.Width;
			swapChainDesc.Height = sd.BufferDesc.Height;
			//swapChainDesc.SampleDesc = sd.SampleDesc;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.Stereo = FALSE;
			swapChainDesc.Scaling = DXGI_SCALING_STRETCH; //this is the implicit behavior of DXGI when you call the IDXGIFactory::CreateSwapChain method.

			DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc;
			ZeroMemory(&fullScreenDesc, sizeof(fullScreenDesc));
			fullScreenDesc.RefreshRate = sd.BufferDesc.RefreshRate;
			fullScreenDesc.Scaling = sd.BufferDesc.Scaling;
			fullScreenDesc.ScanlineOrdering = sd.BufferDesc.ScanlineOrdering;
			fullScreenDesc.Windowed = sd.Windowed;

			hr = pDXGIFactory12->CreateSwapChainForHwnd(
				dxgiDevice,
				hwnd,
				&swapChainDesc,
				&fullScreenDesc,
				nullptr,
				&swap_chain_1_); // Recreate the other swap chain using a slightly modified version of the sent in swap chains description?

			pDXGIFactory12->Release();

			if (hr == S_OK)
			{
				CreateD3DResolver(dxgiDevice); // 
			}
		}

		return hr;
	}

	HRESULT CreateD3DResolver(IUnknown* pDevice)
	{
		HRESULT hr = S_OK;
		IUnknown* pDeviceDummy = nullptr;

		if (SUCCEEDED(hr = pDevice->QueryInterface(__uuidof(ID3D11Device), (void **)&pDeviceDummy)))
		{
			d3d_resolve_ = new D3D11Resolve(); // If we detect D3D11 then use a resolve based on that
		}
		else if (SUCCEEDED(hr = pDevice->QueryInterface(__uuidof(ID3D10Device1), (void **)&pDeviceDummy)))
		{
			//fix
		}
		else if (SUCCEEDED(hr = pDevice->QueryInterface(__uuidof(ID3D10Device), (void **)&pDeviceDummy)))
		{
			//fix
		}

		if (SUCCEEDED(hr))
		{
			d3d_resolve_->Init(pDeviceDummy); // Init the resolve once we have found what version to use
		}

		SAFE_RELEASE(pDeviceDummy); // Have we even utelized this one really? As far as I can see it is just used to ask if there is a real one in the resolves init function

		return hr;
	}

	void CopySharedResources()
	{
		WaitForSingleObject(sharedMutex, INFINITE);

		for (auto& sharedResource : storedResources)
		{
			ID3D11Texture2D* texture = (ID3D11Texture2D*)sharedResource.second.sharedResource;
			D3D11_TEXTURE2D_DESC desc;

			texture->GetDesc(&desc);

			if (desc.ArraySize > 1 || desc.MipLevels > 1)
			{
				for (UINT item = 0; item < desc.ArraySize; ++item)
				{
					for (UINT level = 0; level < desc.MipLevels; ++level)
					{
						UINT index = D3D11CalcSubresource(level, item, desc.MipLevels);
						GlobalDeviceContext->ResolveSubresource(sharedResource.second.sharedResource, index, sharedResource.second.originalResource, index, desc.Format);
					}
				}
			}
			else
			{
				GlobalDeviceContext->CopyResource(sharedResource.second.sharedResource, sharedResource.second.originalResource);
			}
		}
		Sleep(5);// REPLACE WITH FENCE OR QUERY OR SOMETHING!!! WE NEED TO MAKE SURE THE RESOURCE IS DONE COPYING BEFORE WE LET GO OF THE MUTEX
		ReleaseMutex(sharedMutex);
	}

	HRESULT Present1Internal(IDXGISwapChain1* pSwapChain, UINT SyncInterval, UINT Flags, const DXGI_PRESENT_PARAMETERS *pPresentParameters)
	{
		//MessageBoxA(0, "Present1Internal called", "", 0);

		HRESULT hr = S_OK;

		DXGI_SwapChain1_Present1Type oPresent1 = (DXGI_SwapChain1_Present1Type)hook_Present_1_.call; // the function call?
		hook_Present_1_.Restore(); // Restore the original first part of the function so that we can call it
		//Flags &= ~DXGI_PRESENT_RESTRICT_TO_OUTPUT;
		hr = oPresent1(pSwapChain, SyncInterval, Flags, pPresentParameters); // call the function?
		hook_Present_1_.Inject(); // Inject our code back so that the next time we call it we end up here again

		return hr;
	}

	static HRESULT __stdcall Present1(IDXGISwapChain1* pSwapChain, UINT SyncInterval, UINT Flags, const DXGI_PRESENT_PARAMETERS *pPresentParameters) // The entry point for the Present1 call? Is the first argument the "this" pointer?
	{
		return SwapChainOverride::GetInstance()->Present1Internal(pSwapChain, SyncInterval, Flags, pPresentParameters);
	}

	HRESULT PresentInternal(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		//MessageBoxA(0, "Fancy PresentInternal called", "", 0);

		HRESULT hr = S_OK;

		DXGI_SwapChain_PresentType oPresent = (DXGI_SwapChain_PresentType)hook_Present_.call;
		hook_Present_.Restore();
		hr = oPresent(pSwapChain, SyncInterval, Flags);
		hook_Present_.Inject();

		char* message = static_cast<char*>(messageMemory.GetPointer());
		if (message[0] == 'T' && message[1] == 'G' && message[2] == 'R' && message[3] == 'S')
		{
			//MessageBoxA(0, "Found a message!", "", 0);
			unsigned int number = std::stoi(message + 4); // Skip TGRS and get the number
			if (number < rData.size())
				rData[number].useWireframe = !rData[number].useWireframe;

			for (int i = 0; i < 255; ++i)
				*message = 0;
		}

		return hr;


		/*
		Här har du möjlighet att få ut bilden som ritats.

		se: https://msdn.microsoft.com/en-us/library/windows/desktop/bb174570(v=vs.85).aspx

		I demofallet ska du få ut en ID3D11Texture2D, inte ID3D10Texture2D som i länken ovan, exempel:
		ID3D11Texture2D * p_RT;
		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(p_RT), reinterpret_cast<void**>(&p_RT))))
		{
			MessageBoxA(0, "nu har vi texturpekaren :-)", "", 0);
		}

		Tänk på att ALLTID hantera HRESULT-returvärden, många D3D-funktioner returnerar dessa.
		*/


		//MessageBoxA(0, "Fancy PresentInternal called", "", 0);

		//HRESULT hr = S_OK;

		//Flags &= ~DXGI_PRESENT_RESTRICT_TO_OUTPUT;

		//IDXGISwapChain1* ptrSwapChain1 = nullptr;
		//if (FAILED(hr = pSwapChain->QueryInterface(__uuidof(IDXGISwapChain1), (void **)&ptrSwapChain1))) // Fetch the current swap chain?
		//{
		//	ValidateSwapChain1(pSwapChain); // Validate that the swap chain is the one we have?

		//	if (swap_chain_1_ != nullptr)
		//	{
		//		MessageBoxA(0, "Into the NOT a nullptr box we go!", "", 0);
		//		d3d_resolve_->Resolve(pSwapChain, swap_chain_1_);

		//		DXGI_SwapChain_PresentType oPresent = (DXGI_SwapChain_PresentType)hook_Present_.call;
		//		hook_Present_.Restore();
		//		hr = oPresent(pSwapChain, SyncInterval, Flags);
		//		hook_Present_.Inject();

		//		Flags &= ~DXGI_PRESENT_RESTRICT_TO_OUTPUT;
		//		DXGI_PRESENT_PARAMETERS pp;
		//		memset(&pp, 0, sizeof(pp));
		//		hr = swap_chain_1_->Present1(SyncInterval, Flags, &pp);
		//	}
		//}

		//SAFE_RELEASE(ptrSwapChain1);

		//if (swap_chain_1_ == nullptr)
		//{

		//	CopySharedResources();

		//	//MessageBoxA(0, "Into the nullptr box we go!", "", 0);
		//	DXGI_SwapChain_PresentType oPresent = (DXGI_SwapChain_PresentType)hook_Present_.call;
		//	hook_Present_.Restore();
		//	hr = oPresent(pSwapChain, SyncInterval, Flags);
		//	hook_Present_.Inject();
		//}

		//return hr;
	}

	static HRESULT __stdcall Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		return SwapChainOverride::GetInstance()->PresentInternal(pSwapChain, SyncInterval, Flags);
	}

	HRESULT SetFullscreenStateInternal(IDXGISwapChain* pSwapChain, BOOL Fullscreen, IDXGIOutput *pTarget)
	{
		HRESULT hr = S_OK;

		DXGI_SwapChain_SetFullscreenStateType oSetFullscreenState = (DXGI_SwapChain_SetFullscreenStateType)hook_SetFullscreenState_.call;
		hook_SetFullscreenState_.Restore();
		hr = oSetFullscreenState(pSwapChain, Fullscreen, pTarget);
		hook_SetFullscreenState_.Inject();

		return hr;

		//HRESULT hr = S_OK;

		//DXGI_SwapChain_SetFullscreenStateType oSetFullscreenState = (DXGI_SwapChain_SetFullscreenStateType)hook_SetFullscreenState_.call;
		//hook_SetFullscreenState_.Restore();

		//if (swap_chain_1_)
		//{
		//	if (Fullscreen == FALSE)
		//		hr = oSetFullscreenState(pSwapChain, Fullscreen, pTarget);

		//	hr = oSetFullscreenState(swap_chain_1_, Fullscreen, pTarget);
		//}
		//else
		//{
		//	hr = oSetFullscreenState(pSwapChain, Fullscreen, pTarget);
		//}

		//hook_SetFullscreenState_.Inject();

		//return hr;
	}

	static HRESULT __stdcall SetFullscreenState(IDXGISwapChain* pSwapChain, BOOL Fullscreen, IDXGIOutput *pTarget)
	{
		return SwapChainOverride::GetInstance()->SetFullscreenStateInternal(pSwapChain, Fullscreen, pTarget);
	}

	HRESULT GetFullscreenStateInternal(IDXGISwapChain* pSwapChain, BOOL* pFullscreen, IDXGIOutput **ppTarget)
	{
		HRESULT hr = S_OK;

		DXGI_SwapChain_GetFullscreenStateType oGetFullscreenState = (DXGI_SwapChain_GetFullscreenStateType)hook_GetFullscreenState_.call;
		hook_GetFullscreenState_.Restore();
		hr = oGetFullscreenState(pSwapChain, pFullscreen, ppTarget);
		hook_GetFullscreenState_.Inject();

		return hr;

		//HRESULT hr = S_OK;

		//DXGI_SwapChain_GetFullscreenStateType oGetFullscreenState = (DXGI_SwapChain_GetFullscreenStateType)hook_GetFullscreenState_.call;
		//hook_GetFullscreenState_.Restore();

		//if (swap_chain_1_)
		//	hr = oGetFullscreenState(swap_chain_1_, pFullscreen, ppTarget);
		//else
		//	hr = oGetFullscreenState(pSwapChain, pFullscreen, ppTarget);
		//hook_GetFullscreenState_.Inject();

		//return hr;
	}

	static HRESULT __stdcall GetFullscreenState(IDXGISwapChain* pSwapChain, BOOL* pFullscreen, IDXGIOutput **ppTarget)
	{
		return SwapChainOverride::GetInstance()->GetFullscreenStateInternal(pSwapChain, pFullscreen, ppTarget);
	}

	HRESULT ResizeBuffersInternal(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		HRESULT hr = S_OK;

		DXGI_SwapChain_ResizeBuffersType oResizeBuffers = (DXGI_SwapChain_ResizeBuffersType)hook_ResizeBuffers_.call;
		hook_ResizeBuffers_.Restore();
		hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
		hook_ResizeBuffers_.Inject();

		return hr;

		//HRESULT hr = S_OK;

		//DXGI_SwapChain_ResizeBuffersType oResizeBuffers = (DXGI_SwapChain_ResizeBuffersType)hook_ResizeBuffers_.call;
		//hook_ResizeBuffers_.Restore();

		//SwapChainFlags &= ~DXGI_PRESENT_RESTRICT_TO_OUTPUT;

		//if (swap_chain_1_)
		//{
		//	hr = oResizeBuffers(swap_chain_1_, BufferCount, Width, Height, NewFormat, SwapChainFlags);
		//}

		//hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
		//hook_ResizeBuffers_.Inject();

		//return hr;
	}

	static HRESULT __stdcall ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		return SwapChainOverride::GetInstance()->ResizeBuffersInternal(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	}

	HRESULT ResizeTargetInternal(IDXGISwapChain* pSwapChain, const DXGI_MODE_DESC *pNewTargetParameters)
	{
		HRESULT hr = S_OK;

		DXGI_SwapChain_ResizeTargetType oResizeTarget = (DXGI_SwapChain_ResizeTargetType)hook_ResizeTarget_.call;
		hook_ResizeTarget_.Restore();
		hr = oResizeTarget(pSwapChain, pNewTargetParameters);
		hook_ResizeTarget_.Inject();

		return hr;

		//HRESULT hr = S_OK;

		//DXGI_SwapChain_ResizeTargetType oResizeTarget = (DXGI_SwapChain_ResizeTargetType)hook_ResizeTarget_.call;
		//hook_ResizeTarget_.Restore();

		//if (swap_chain_1_)
		//{
		//	hr = oResizeTarget(swap_chain_1_, pNewTargetParameters);
		//}
		//hr = oResizeTarget(pSwapChain, pNewTargetParameters);
		//hook_ResizeTarget_.Inject();

		//return hr;
	}

	static HRESULT __stdcall ResizeTarget(IDXGISwapChain* pSwapChain, const DXGI_MODE_DESC *pNewTargetParameters)
	{
		return SwapChainOverride::GetInstance()->ResizeTargetInternal(pSwapChain, pNewTargetParameters);
	}
};

SwapChainOverride* SwapChainOverride::instance_ = nullptr;
SwapChainOverride* SwapChainOverride::GetInstance()
{
	if (!instance_)
		instance_ = myNew SwapChainOverride();

	return instance_;
}