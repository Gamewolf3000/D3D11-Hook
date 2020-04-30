#include "FakeIDXGIFactory.h"

HRESULT __stdcall FakeIDXGIFactory::QueryInterface(REFIID riid, void ** ppvObject)
{
	return HRESULT __stdcall();
}

ULONG __stdcall FakeIDXGIFactory::AddRef(void)
{
	return 0;
}

ULONG __stdcall FakeIDXGIFactory::Release(void)
{
	return 0;
}

HRESULT __stdcall FakeIDXGIFactory::SetPrivateData(REFGUID Name, UINT DataSize, const void * pData)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::SetPrivateDataInterface(REFGUID Name, const IUnknown * pUnknown)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::GetPrivateData(REFGUID Name, UINT * pDataSize, void * pData)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::GetParent(REFIID riid, void ** ppParent)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::EnumAdapters(UINT Adapter, IDXGIAdapter ** ppAdapter)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::GetWindowAssociation(HWND * pWindowHandle)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::CreateSwapChain(IUnknown * pDevice, DXGI_SWAP_CHAIN_DESC * pDesc, IDXGISwapChain ** ppSwapChain)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter ** ppAdapter)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::EnumAdapters1(UINT Adapter, IDXGIAdapter1 ** ppAdapter)
{
	return HRESULT __stdcall();
}

BOOL __stdcall FakeIDXGIFactory::IsCurrent(void)
{
	return 0;
}

BOOL __stdcall FakeIDXGIFactory::IsWindowedStereoEnabled(void)
{
	return 0;
}

HRESULT __stdcall FakeIDXGIFactory::CreateSwapChainForHwnd(IUnknown * pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1 * pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC * pFullscreenDesc, IDXGIOutput * pRestrictToOutput, IDXGISwapChain1 ** ppSwapChain)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::CreateSwapChainForCoreWindow(IUnknown * pDevice, IUnknown * pWindow, const DXGI_SWAP_CHAIN_DESC1 * pDesc, IDXGIOutput * pRestrictToOutput, IDXGISwapChain1 ** ppSwapChain)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::GetSharedResourceAdapterLuid(HANDLE hResource, LUID * pLuid)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD * pdwCookie)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::RegisterStereoStatusEvent(HANDLE hEvent, DWORD * pdwCookie)
{
	return HRESULT __stdcall();
}

void __stdcall FakeIDXGIFactory::UnregisterStereoStatus(DWORD dwCookie)
{
	return void __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD * pdwCookie)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD * pdwCookie)
{
	return HRESULT __stdcall();
}

void __stdcall FakeIDXGIFactory::UnregisterOcclusionStatus(DWORD dwCookie)
{
	return void __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::CreateSwapChainForComposition(IUnknown * pDevice, const DXGI_SWAP_CHAIN_DESC1 * pDesc, IDXGIOutput * pRestrictToOutput, IDXGISwapChain1 ** ppSwapChain)
{
	return HRESULT __stdcall();
}

UINT __stdcall FakeIDXGIFactory::GetCreationFlags(void)
{
	return 0;
}

HRESULT __stdcall FakeIDXGIFactory::EnumAdapterByLuid(LUID AdapterLuid, REFIID riid, void ** ppvAdapter)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::EnumWarpAdapter(REFIID riid, void ** ppvAdapter)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::CheckFeatureSupport(DXGI_FEATURE Feature, void * pFeatureSupportData, UINT FeatureSupportDataSize)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeIDXGIFactory::EnumAdapterByGpuPreference(UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference, REFIID riid, void ** ppvAdapter)
{
	return HRESULT __stdcall();
}
