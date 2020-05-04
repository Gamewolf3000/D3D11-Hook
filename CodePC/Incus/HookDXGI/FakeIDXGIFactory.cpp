#include "FakeIDXGIFactory.h"
#include "FakeID3D11Device.hpp"
#include "FakeIDXGISwapChain.h"

FakeIDXGIFactory::FakeIDXGIFactory(IDXGIFactory * real)
{
	realFactory = static_cast<IDXGIFactory6*>(real);
}

HRESULT __stdcall FakeIDXGIFactory::QueryInterface(REFIID riid, void ** ppvObject)
{
	return realFactory->QueryInterface(riid, ppvObject);
}

ULONG __stdcall FakeIDXGIFactory::AddRef(void)
{
	return realFactory->AddRef();
}

ULONG __stdcall FakeIDXGIFactory::Release(void)
{
	return realFactory->Release();
}

HRESULT __stdcall FakeIDXGIFactory::SetPrivateData(REFGUID Name, UINT DataSize, const void * pData)
{
	return realFactory->SetPrivateData(Name, DataSize, pData);
}

HRESULT __stdcall FakeIDXGIFactory::SetPrivateDataInterface(REFGUID Name, const IUnknown * pUnknown)
{
	return realFactory->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT __stdcall FakeIDXGIFactory::GetPrivateData(REFGUID Name, UINT * pDataSize, void * pData)
{
	return realFactory->GetPrivateData(Name, pDataSize, pData);
}

HRESULT __stdcall FakeIDXGIFactory::GetParent(REFIID riid, void ** ppParent)
{
	return realFactory->GetParent(riid, ppParent);
}

HRESULT __stdcall FakeIDXGIFactory::EnumAdapters(UINT Adapter, IDXGIAdapter ** ppAdapter)
{
	return realFactory->EnumAdapters(Adapter, ppAdapter);
}

HRESULT __stdcall FakeIDXGIFactory::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
	return realFactory->MakeWindowAssociation(WindowHandle, Flags);
}

HRESULT __stdcall FakeIDXGIFactory::GetWindowAssociation(HWND * pWindowHandle)
{
	return realFactory->GetWindowAssociation(pWindowHandle);
}

HRESULT __stdcall FakeIDXGIFactory::CreateSwapChain(IUnknown * pDevice, DXGI_SWAP_CHAIN_DESC * pDesc, IDXGISwapChain ** ppSwapChain)
{
	auto device = static_cast<FakeID3D11Device*>(pDevice)->GetReal();
	HRESULT hr = realFactory->CreateSwapChain(device, pDesc, ppSwapChain);
	if (hr == S_OK)
	{
		FakeIDXGISwapChain* swapChain = new FakeIDXGISwapChain(*ppSwapChain);
		*ppSwapChain = swapChain;
	}
	return hr;
}

HRESULT __stdcall FakeIDXGIFactory::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter ** ppAdapter)
{
	return realFactory->CreateSoftwareAdapter(Module, ppAdapter);
}

HRESULT __stdcall FakeIDXGIFactory::EnumAdapters1(UINT Adapter, IDXGIAdapter1 ** ppAdapter)
{
	return realFactory->EnumAdapters1(Adapter, ppAdapter);
}

BOOL __stdcall FakeIDXGIFactory::IsCurrent(void)
{
	return realFactory->IsCurrent();
}

BOOL __stdcall FakeIDXGIFactory::IsWindowedStereoEnabled(void)
{
	return realFactory->IsWindowedStereoEnabled();
}

HRESULT __stdcall FakeIDXGIFactory::CreateSwapChainForHwnd(IUnknown * pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1 * pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC * pFullscreenDesc, IDXGIOutput * pRestrictToOutput, IDXGISwapChain1 ** ppSwapChain)
{
	auto device = static_cast<FakeID3D11Device*>(pDevice)->GetReal();
	HRESULT hr = realFactory->CreateSwapChainForHwnd(device, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain);
	if (hr == S_OK)
	{
		FakeIDXGISwapChain* swapChain = new FakeIDXGISwapChain(*ppSwapChain);
		*ppSwapChain = swapChain;
	}
	return hr;
}

HRESULT __stdcall FakeIDXGIFactory::CreateSwapChainForCoreWindow(IUnknown * pDevice, IUnknown * pWindow, const DXGI_SWAP_CHAIN_DESC1 * pDesc, IDXGIOutput * pRestrictToOutput, IDXGISwapChain1 ** ppSwapChain)
{
	auto device = static_cast<FakeID3D11Device*>(pDevice)->GetReal();
	HRESULT hr = realFactory->CreateSwapChainForCoreWindow(device, pWindow, pDesc, pRestrictToOutput, ppSwapChain);
	if (hr == S_OK)
	{
		FakeIDXGISwapChain* swapChain = new FakeIDXGISwapChain(*ppSwapChain);
		*ppSwapChain = swapChain;
	}
	return hr;
}

HRESULT __stdcall FakeIDXGIFactory::GetSharedResourceAdapterLuid(HANDLE hResource, LUID * pLuid)
{
	return realFactory->GetSharedResourceAdapterLuid(hResource, pLuid);
}

HRESULT __stdcall FakeIDXGIFactory::RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD * pdwCookie)
{
	return realFactory->RegisterStereoStatusWindow(WindowHandle, wMsg, pdwCookie);
}

HRESULT __stdcall FakeIDXGIFactory::RegisterStereoStatusEvent(HANDLE hEvent, DWORD * pdwCookie)
{
	return realFactory->RegisterStereoStatusEvent(hEvent, pdwCookie);
}

void __stdcall FakeIDXGIFactory::UnregisterStereoStatus(DWORD dwCookie)
{
	realFactory->UnregisterStereoStatus(dwCookie);
}

HRESULT __stdcall FakeIDXGIFactory::RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD * pdwCookie)
{
	return realFactory->RegisterOcclusionStatusWindow(WindowHandle, wMsg, pdwCookie);
}

HRESULT __stdcall FakeIDXGIFactory::RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD * pdwCookie)
{
	return realFactory->RegisterOcclusionStatusEvent(hEvent, pdwCookie);
}

void __stdcall FakeIDXGIFactory::UnregisterOcclusionStatus(DWORD dwCookie)
{
	realFactory->UnregisterOcclusionStatus(dwCookie);
}

HRESULT __stdcall FakeIDXGIFactory::CreateSwapChainForComposition(IUnknown * pDevice, const DXGI_SWAP_CHAIN_DESC1 * pDesc, IDXGIOutput * pRestrictToOutput, IDXGISwapChain1 ** ppSwapChain)
{
	auto device = static_cast<FakeID3D11Device*>(pDevice)->GetReal();
	HRESULT hr = realFactory->CreateSwapChainForComposition(device, pDesc, pRestrictToOutput, ppSwapChain);
	if (hr == S_OK)
	{
		FakeIDXGISwapChain* swapChain = new FakeIDXGISwapChain(*ppSwapChain);
		*ppSwapChain = swapChain;
	}
	return hr;
}

UINT __stdcall FakeIDXGIFactory::GetCreationFlags(void)
{
	return realFactory->GetCreationFlags();
}

HRESULT __stdcall FakeIDXGIFactory::EnumAdapterByLuid(LUID AdapterLuid, REFIID riid, void ** ppvAdapter)
{
	return realFactory->EnumAdapterByLuid(AdapterLuid, riid, ppvAdapter);
}

HRESULT __stdcall FakeIDXGIFactory::EnumWarpAdapter(REFIID riid, void ** ppvAdapter)
{
	return realFactory->EnumWarpAdapter(riid, ppvAdapter);
}

HRESULT __stdcall FakeIDXGIFactory::CheckFeatureSupport(DXGI_FEATURE Feature, void * pFeatureSupportData, UINT FeatureSupportDataSize)
{
	return realFactory->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
}

HRESULT __stdcall FakeIDXGIFactory::EnumAdapterByGpuPreference(UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference, REFIID riid, void ** ppvAdapter)
{
	return realFactory->EnumAdapterByGpuPreference(Adapter, GpuPreference, riid, ppvAdapter);
}
