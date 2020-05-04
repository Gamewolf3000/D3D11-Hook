#pragma once

#include <dxgi1_6.h>

class FakeIDXGISwapChain : public IDXGISwapChain4
{
private:
	IDXGISwapChain4* realSwapChain;

public:
	FakeIDXGISwapChain(IDXGISwapChain* real);

	// Inherited via IDXGISwapChain4 (42)
	template<typename Q>
	HRESULT __stdcall QueryInterface(Q ** pp);
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void ** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;
	virtual HRESULT __stdcall SetPrivateData(REFGUID Name, UINT DataSize, const void * pData) override;
	virtual HRESULT __stdcall SetPrivateDataInterface(REFGUID Name, const IUnknown * pUnknown) override;
	virtual HRESULT __stdcall GetPrivateData(REFGUID Name, UINT * pDataSize, void * pData) override;
	virtual HRESULT __stdcall GetParent(REFIID riid, void ** ppParent) override;
	virtual HRESULT __stdcall GetDevice(REFIID riid, void ** ppDevice) override;
	virtual HRESULT __stdcall Present(UINT SyncInterval, UINT Flags) override;
	virtual HRESULT __stdcall GetBuffer(UINT Buffer, REFIID riid, void ** ppSurface) override;
	virtual HRESULT __stdcall SetFullscreenState(BOOL Fullscreen, IDXGIOutput * pTarget) override;
	virtual HRESULT __stdcall GetFullscreenState(BOOL * pFullscreen, IDXGIOutput ** ppTarget) override;
	virtual HRESULT __stdcall GetDesc(DXGI_SWAP_CHAIN_DESC * pDesc) override;
	virtual HRESULT __stdcall ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) override;
	virtual HRESULT __stdcall ResizeTarget(const DXGI_MODE_DESC * pNewTargetParameters) override;
	virtual HRESULT __stdcall GetContainingOutput(IDXGIOutput ** ppOutput) override;
	virtual HRESULT __stdcall GetFrameStatistics(DXGI_FRAME_STATISTICS * pStats) override;
	virtual HRESULT __stdcall GetLastPresentCount(UINT * pLastPresentCount) override;
	virtual HRESULT __stdcall GetDesc1(DXGI_SWAP_CHAIN_DESC1 * pDesc) override;
	virtual HRESULT __stdcall GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC * pDesc) override;
	virtual HRESULT __stdcall GetHwnd(HWND * pHwnd) override;
	virtual HRESULT __stdcall GetCoreWindow(REFIID refiid, void ** ppUnk) override;
	virtual HRESULT __stdcall Present1(UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS * pPresentParameters) override;
	virtual BOOL __stdcall IsTemporaryMonoSupported(void) override;
	virtual HRESULT __stdcall GetRestrictToOutput(IDXGIOutput ** ppRestrictToOutput) override;
	virtual HRESULT __stdcall SetBackgroundColor(const DXGI_RGBA * pColor) override;
	virtual HRESULT __stdcall GetBackgroundColor(DXGI_RGBA * pColor) override;
	virtual HRESULT __stdcall SetRotation(DXGI_MODE_ROTATION Rotation) override;
	virtual HRESULT __stdcall GetRotation(DXGI_MODE_ROTATION * pRotation) override;
	virtual HRESULT __stdcall SetSourceSize(UINT Width, UINT Height) override;
	virtual HRESULT __stdcall GetSourceSize(UINT * pWidth, UINT * pHeight) override;
	virtual HRESULT __stdcall SetMaximumFrameLatency(UINT MaxLatency) override;
	virtual HRESULT __stdcall GetMaximumFrameLatency(UINT * pMaxLatency) override;
	virtual HANDLE __stdcall GetFrameLatencyWaitableObject(void) override;
	virtual HRESULT __stdcall SetMatrixTransform(const DXGI_MATRIX_3X2_F * pMatrix) override;
	virtual HRESULT __stdcall GetMatrixTransform(DXGI_MATRIX_3X2_F * pMatrix) override;
	virtual UINT __stdcall GetCurrentBackBufferIndex(void) override;
	virtual HRESULT __stdcall CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE ColorSpace, UINT * pColorSpaceSupport) override;
	virtual HRESULT __stdcall SetColorSpace1(DXGI_COLOR_SPACE_TYPE ColorSpace) override;
	virtual HRESULT __stdcall ResizeBuffers1(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format, UINT SwapChainFlags, const UINT * pCreationNodeMask, IUnknown * const * ppPresentQueue) override;
	virtual HRESULT __stdcall SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void * pMetaData) override;
};

template<typename Q>
inline HRESULT __stdcall FakeIDXGISwapChain::QueryInterface(_COM_Outptr_ Q ** pp)
{
	return QueryInterface(__uuidof(Q), (void **)pp);
}
