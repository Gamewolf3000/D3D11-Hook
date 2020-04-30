#include "FakeIDXGISwapChain.h"

HRESULT __stdcall FakeIDXGISwapChain::QueryInterface(REFIID riid, void ** ppvObject)
{
	return realSwapChain->QueryInterface(riid, ppvObject);
}

ULONG __stdcall FakeIDXGISwapChain::AddRef(void)
{
	return realSwapChain->AddRef();
}

ULONG __stdcall FakeIDXGISwapChain::Release(void)
{
	return realSwapChain->Release();
}

HRESULT __stdcall FakeIDXGISwapChain::SetPrivateData(REFGUID Name, UINT DataSize, const void * pData)
{
	return realSwapChain->SetPrivateData(Name, DataSize, pData);
}

HRESULT __stdcall FakeIDXGISwapChain::SetPrivateDataInterface(REFGUID Name, const IUnknown * pUnknown)
{
	return realSwapChain->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT __stdcall FakeIDXGISwapChain::GetPrivateData(REFGUID Name, UINT * pDataSize, void * pData)
{
	return realSwapChain->GetPrivateData(Name, pDataSize, pData);
}

HRESULT __stdcall FakeIDXGISwapChain::GetParent(REFIID riid, void ** ppParent)
{
	return realSwapChain->GetParent(riid, ppParent);
}

HRESULT __stdcall FakeIDXGISwapChain::GetDevice(REFIID riid, void ** ppDevice)
{
	return realSwapChain->GetDevice(riid, ppDevice);
}

HRESULT __stdcall FakeIDXGISwapChain::Present(UINT SyncInterval, UINT Flags)
{
	return realSwapChain->Present(SyncInterval, Flags);
}

HRESULT __stdcall FakeIDXGISwapChain::GetBuffer(UINT Buffer, REFIID riid, void ** ppSurface)
{
	return realSwapChain->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT __stdcall FakeIDXGISwapChain::SetFullscreenState(BOOL Fullscreen, IDXGIOutput * pTarget)
{
	return realSwapChain->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT __stdcall FakeIDXGISwapChain::GetFullscreenState(BOOL * pFullscreen, IDXGIOutput ** ppTarget)
{
	return realSwapChain->GetFullscreenState(pFullscreen, ppTarget);
}

HRESULT __stdcall FakeIDXGISwapChain::GetDesc(DXGI_SWAP_CHAIN_DESC * pDesc)
{
	return realSwapChain->GetDesc(pDesc);
}

HRESULT __stdcall FakeIDXGISwapChain::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	return realSwapChain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT __stdcall FakeIDXGISwapChain::ResizeTarget(const DXGI_MODE_DESC * pNewTargetParameters)
{
	return realSwapChain->ResizeTarget(pNewTargetParameters);
}

HRESULT __stdcall FakeIDXGISwapChain::GetContainingOutput(IDXGIOutput ** ppOutput)
{
	return realSwapChain->GetContainingOutput(ppOutput);
}

HRESULT __stdcall FakeIDXGISwapChain::GetFrameStatistics(DXGI_FRAME_STATISTICS * pStats)
{
	return realSwapChain->GetFrameStatistics(pStats);
}

HRESULT __stdcall FakeIDXGISwapChain::GetLastPresentCount(UINT * pLastPresentCount)
{
	return realSwapChain->GetLastPresentCount(pLastPresentCount);
}

HRESULT __stdcall FakeIDXGISwapChain::GetDesc1(DXGI_SWAP_CHAIN_DESC1 * pDesc)
{
	return realSwapChain->GetDesc1(pDesc);
}

HRESULT __stdcall FakeIDXGISwapChain::GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC * pDesc)
{
	return realSwapChain->GetFullscreenDesc(pDesc);
}

HRESULT __stdcall FakeIDXGISwapChain::GetHwnd(HWND * pHwnd)
{
	return realSwapChain->GetHwnd(pHwnd);
}

HRESULT __stdcall FakeIDXGISwapChain::GetCoreWindow(REFIID refiid, void ** ppUnk)
{
	return realSwapChain->GetCoreWindow(refiid, ppUnk);
}

HRESULT __stdcall FakeIDXGISwapChain::Present1(UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS * pPresentParameters)
{
	return realSwapChain->Present1(SyncInterval, PresentFlags, pPresentParameters);
}

BOOL __stdcall FakeIDXGISwapChain::IsTemporaryMonoSupported(void)
{
	return realSwapChain->IsTemporaryMonoSupported();
}

HRESULT __stdcall FakeIDXGISwapChain::GetRestrictToOutput(IDXGIOutput ** ppRestrictToOutput)
{
	return realSwapChain->GetRestrictToOutput(ppRestrictToOutput);
}

HRESULT __stdcall FakeIDXGISwapChain::SetBackgroundColor(const DXGI_RGBA * pColor)
{
	return realSwapChain->SetBackgroundColor(pColor);
}

HRESULT __stdcall FakeIDXGISwapChain::GetBackgroundColor(DXGI_RGBA * pColor)
{
	return realSwapChain->GetBackgroundColor(pColor);
}

HRESULT __stdcall FakeIDXGISwapChain::SetRotation(DXGI_MODE_ROTATION Rotation)
{
	return realSwapChain->SetRotation(Rotation);
}

HRESULT __stdcall FakeIDXGISwapChain::GetRotation(DXGI_MODE_ROTATION * pRotation)
{
	return realSwapChain->GetRotation(pRotation);
}

HRESULT __stdcall FakeIDXGISwapChain::SetSourceSize(UINT Width, UINT Height)
{
	return realSwapChain->SetSourceSize(Width, Height);
}

HRESULT __stdcall FakeIDXGISwapChain::GetSourceSize(UINT * pWidth, UINT * pHeight)
{
	return realSwapChain->GetSourceSize(pWidth, pHeight);
}

HRESULT __stdcall FakeIDXGISwapChain::SetMaximumFrameLatency(UINT MaxLatency)
{
	return realSwapChain->SetMaximumFrameLatency(MaxLatency);
}

HRESULT __stdcall FakeIDXGISwapChain::GetMaximumFrameLatency(UINT * pMaxLatency)
{
	return realSwapChain->GetMaximumFrameLatency(pMaxLatency);
}

HANDLE __stdcall FakeIDXGISwapChain::GetFrameLatencyWaitableObject(void)
{
	return realSwapChain->GetFrameLatencyWaitableObject();
}

HRESULT __stdcall FakeIDXGISwapChain::SetMatrixTransform(const DXGI_MATRIX_3X2_F * pMatrix)
{
	return realSwapChain->SetMatrixTransform(pMatrix);
}

HRESULT __stdcall FakeIDXGISwapChain::GetMatrixTransform(DXGI_MATRIX_3X2_F * pMatrix)
{
	return realSwapChain->GetMatrixTransform(pMatrix);
}

UINT __stdcall FakeIDXGISwapChain::GetCurrentBackBufferIndex(void)
{
	return realSwapChain->GetCurrentBackBufferIndex();
}

HRESULT __stdcall FakeIDXGISwapChain::CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE ColorSpace, UINT * pColorSpaceSupport)
{
	return realSwapChain->CheckColorSpaceSupport(ColorSpace, pColorSpaceSupport);
}

HRESULT __stdcall FakeIDXGISwapChain::SetColorSpace1(DXGI_COLOR_SPACE_TYPE ColorSpace)
{
	return realSwapChain->SetColorSpace1(ColorSpace);
}

HRESULT __stdcall FakeIDXGISwapChain::ResizeBuffers1(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format, UINT SwapChainFlags, const UINT * pCreationNodeMask, IUnknown * const * ppPresentQueue)
{
	return realSwapChain->ResizeBuffers1(BufferCount, Width, Height, Format, SwapChainFlags, pCreationNodeMask, ppPresentQueue);
}

HRESULT __stdcall FakeIDXGISwapChain::SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void * pMetaData)
{
	return realSwapChain->SetHDRMetaData(Type, Size, pMetaData);
}
