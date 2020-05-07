#pragma once

#include <dxgi1_6.h>

class FakeIDXGIFactory : public IDXGIFactory6
{
private:
	IDXGIFactory6* realFactory;

public:
	FakeIDXGIFactory(IDXGIFactory* real);

	// Inherited via IDXGIFactory6
	template<typename Q>
	HRESULT __stdcall QueryInterface(Q ** pp) override;
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void ** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;
	virtual HRESULT __stdcall SetPrivateData(REFGUID Name, UINT DataSize, const void * pData) override;
	virtual HRESULT __stdcall SetPrivateDataInterface(REFGUID Name, const IUnknown * pUnknown) override;
	virtual HRESULT __stdcall GetPrivateData(REFGUID Name, UINT * pDataSize, void * pData) override;
	virtual HRESULT __stdcall GetParent(REFIID riid, void ** ppParent) override;
	virtual HRESULT __stdcall EnumAdapters(UINT Adapter, IDXGIAdapter ** ppAdapter) override;
	virtual HRESULT __stdcall MakeWindowAssociation(HWND WindowHandle, UINT Flags) override;
	virtual HRESULT __stdcall GetWindowAssociation(HWND * pWindowHandle) override;
	virtual HRESULT __stdcall CreateSwapChain(IUnknown * pDevice, DXGI_SWAP_CHAIN_DESC * pDesc, IDXGISwapChain ** ppSwapChain) override;
	virtual HRESULT __stdcall CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter ** ppAdapter) override;
	virtual HRESULT __stdcall EnumAdapters1(UINT Adapter, IDXGIAdapter1 ** ppAdapter) override;
	virtual BOOL __stdcall IsCurrent(void) override;
	virtual BOOL __stdcall IsWindowedStereoEnabled(void) override;
	virtual HRESULT __stdcall CreateSwapChainForHwnd(IUnknown * pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1 * pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC * pFullscreenDesc, IDXGIOutput * pRestrictToOutput, IDXGISwapChain1 ** ppSwapChain) override;
	virtual HRESULT __stdcall CreateSwapChainForCoreWindow(IUnknown * pDevice, IUnknown * pWindow, const DXGI_SWAP_CHAIN_DESC1 * pDesc, IDXGIOutput * pRestrictToOutput, IDXGISwapChain1 ** ppSwapChain) override;
	virtual HRESULT __stdcall GetSharedResourceAdapterLuid(HANDLE hResource, LUID * pLuid) override;
	virtual HRESULT __stdcall RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD * pdwCookie) override;
	virtual HRESULT __stdcall RegisterStereoStatusEvent(HANDLE hEvent, DWORD * pdwCookie) override;
	virtual void __stdcall UnregisterStereoStatus(DWORD dwCookie) override;
	virtual HRESULT __stdcall RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD * pdwCookie) override;
	virtual HRESULT __stdcall RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD * pdwCookie) override;
	virtual void __stdcall UnregisterOcclusionStatus(DWORD dwCookie) override;
	virtual HRESULT __stdcall CreateSwapChainForComposition(IUnknown * pDevice, const DXGI_SWAP_CHAIN_DESC1 * pDesc, IDXGIOutput * pRestrictToOutput, IDXGISwapChain1 ** ppSwapChain) override;
	virtual UINT __stdcall GetCreationFlags(void) override;
	virtual HRESULT __stdcall EnumAdapterByLuid(LUID AdapterLuid, REFIID riid, void ** ppvAdapter) override;
	virtual HRESULT __stdcall EnumWarpAdapter(REFIID riid, void ** ppvAdapter) override;
	virtual HRESULT __stdcall CheckFeatureSupport(DXGI_FEATURE Feature, void * pFeatureSupportData, UINT FeatureSupportDataSize) override;
	virtual HRESULT __stdcall EnumAdapterByGpuPreference(UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference, REFIID riid, void ** ppvAdapter) override;
};

template<typename Q>
inline HRESULT __stdcall FakeIDXGIFactory::QueryInterface(_COM_Outptr_ Q ** pp)
{
	return QueryInterface(__uuidof(Q), (void **)pp);
}
