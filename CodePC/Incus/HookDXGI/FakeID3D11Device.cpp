#include "FakeID3D11Device.hpp"
#include "FakeID3D11DeviceContext.h"

FakeID3D11Device::FakeID3D11Device(ID3D11Device * real) : ID3D11Device5()
{
	realDevice = static_cast<ID3D11Device5*>(real);
}

void FakeID3D11Device::SetImmediateContext(FakeID3D11DeviceContext * context)
{
	immediateContext = context;
}

HRESULT __stdcall FakeID3D11Device::QueryInterface(REFIID riid, void ** ppvObject)
{
	return realDevice->QueryInterface(riid, ppvObject);
}

ULONG __stdcall FakeID3D11Device::AddRef(void)
{
	return realDevice->AddRef();
}

ULONG __stdcall FakeID3D11Device::Release(void)
{
	return realDevice->Release();
}

HRESULT __stdcall FakeID3D11Device::CreateBuffer(const D3D11_BUFFER_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Buffer ** ppBuffer)
{
	return realDevice->CreateBuffer(pDesc, pInitialData, ppBuffer);
}

HRESULT __stdcall FakeID3D11Device::CreateTexture1D(const D3D11_TEXTURE1D_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture1D ** ppTexture1D)
{
	return realDevice->CreateTexture1D(pDesc, pInitialData, ppTexture1D);
}

HRESULT __stdcall FakeID3D11Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture2D ** ppTexture2D)
{
	return realDevice->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
}

HRESULT __stdcall FakeID3D11Device::CreateTexture3D(const D3D11_TEXTURE3D_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture3D ** ppTexture3D)
{
	return realDevice->CreateTexture3D(pDesc, pInitialData, ppTexture3D);
}

HRESULT __stdcall FakeID3D11Device::CreateShaderResourceView(ID3D11Resource * pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC * pDesc, ID3D11ShaderResourceView ** ppSRView)
{
	return realDevice->CreateShaderResourceView(pResource, pDesc, ppSRView);
}

HRESULT __stdcall FakeID3D11Device::CreateUnorderedAccessView(ID3D11Resource * pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC * pDesc, ID3D11UnorderedAccessView ** ppUAView)
{
	return realDevice->CreateUnorderedAccessView(pResource, pDesc, ppUAView);
}

HRESULT __stdcall FakeID3D11Device::CreateRenderTargetView(ID3D11Resource * pResource, const D3D11_RENDER_TARGET_VIEW_DESC * pDesc, ID3D11RenderTargetView ** ppRTView)
{
	return realDevice->CreateRenderTargetView(pResource, pDesc, ppRTView);
}

HRESULT __stdcall FakeID3D11Device::CreateDepthStencilView(ID3D11Resource * pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC * pDesc, ID3D11DepthStencilView ** ppDepthStencilView)
{
	return realDevice->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
}

HRESULT __stdcall FakeID3D11Device::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC * pInputElementDescs, UINT NumElements, const void * pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout ** ppInputLayout)
{
	return realDevice->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
}

HRESULT __stdcall FakeID3D11Device::CreateVertexShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11VertexShader ** ppVertexShader)
{
	++info.numberOfCreatedVertexShaders;
	return realDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
}

HRESULT __stdcall FakeID3D11Device::CreateGeometryShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11GeometryShader ** ppGeometryShader)
{
	++info.numberOfCreatedGeometryShaders;
	return realDevice->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
}

HRESULT __stdcall FakeID3D11Device::CreateGeometryShaderWithStreamOutput(const void * pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY * pSODeclaration, UINT NumEntries, const UINT * pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage * pClassLinkage, ID3D11GeometryShader ** ppGeometryShader)
{
	++info.numberOfCreatedGeometryShaders;
	return realDevice->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
}

HRESULT __stdcall FakeID3D11Device::CreatePixelShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11PixelShader ** ppPixelShader)
{
	++info.numberOfCreatedPixelShaders;
	return realDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
}

HRESULT __stdcall FakeID3D11Device::CreateHullShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11HullShader ** ppHullShader)
{
	++info.numberOfCreatedHullShaders;
	return realDevice->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
}

HRESULT __stdcall FakeID3D11Device::CreateDomainShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11DomainShader ** ppDomainShader)
{
	++info.numberOfCreatedDomainShaders;
	return realDevice->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
}

HRESULT __stdcall FakeID3D11Device::CreateComputeShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11ComputeShader ** ppComputeShader)
{
	++info.numberOfCreatedComputeShaders;
	return realDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
}

HRESULT __stdcall FakeID3D11Device::CreateClassLinkage(ID3D11ClassLinkage ** ppLinkage)
{
	return realDevice->CreateClassLinkage(ppLinkage);
}

HRESULT __stdcall FakeID3D11Device::CreateBlendState(const D3D11_BLEND_DESC * pBlendStateDesc, ID3D11BlendState ** ppBlendState)
{
	return realDevice->CreateBlendState(pBlendStateDesc, ppBlendState);
}

HRESULT __stdcall FakeID3D11Device::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC * pDepthStencilDesc, ID3D11DepthStencilState ** ppDepthStencilState)
{
	return realDevice->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
}

HRESULT __stdcall FakeID3D11Device::CreateRasterizerState(const D3D11_RASTERIZER_DESC * pRasterizerDesc, ID3D11RasterizerState ** ppRasterizerState)
{
	return realDevice->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
}

HRESULT __stdcall FakeID3D11Device::CreateSamplerState(const D3D11_SAMPLER_DESC * pSamplerDesc, ID3D11SamplerState ** ppSamplerState)
{
	return realDevice->CreateSamplerState(pSamplerDesc, ppSamplerState);
}

HRESULT __stdcall FakeID3D11Device::CreateQuery(const D3D11_QUERY_DESC * pQueryDesc, ID3D11Query ** ppQuery)
{
	return realDevice->CreateQuery(pQueryDesc, ppQuery);
}

HRESULT __stdcall FakeID3D11Device::CreatePredicate(const D3D11_QUERY_DESC * pPredicateDesc, ID3D11Predicate ** ppPredicate)
{
	return realDevice->CreatePredicate(pPredicateDesc, ppPredicate);
}

HRESULT __stdcall FakeID3D11Device::CreateCounter(const D3D11_COUNTER_DESC * pCounterDesc, ID3D11Counter ** ppCounter)
{
	return realDevice->CreateCounter(pCounterDesc, ppCounter);
}

HRESULT __stdcall FakeID3D11Device::CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext ** ppDeferredContext)
{
	HRESULT result = realDevice->CreateDeferredContext(ContextFlags, ppDeferredContext);
	if (result == S_OK)
	{
		FakeID3D11DeviceContext* fake = new FakeID3D11DeviceContext(*ppDeferredContext, this);
		*ppDeferredContext = fake;
		++info.numberOfCreatedContexts;
	}
	return result;
}

HRESULT __stdcall FakeID3D11Device::OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void ** ppResource)
{
	return realDevice->OpenSharedResource(hResource, ReturnedInterface, ppResource);
}

HRESULT __stdcall FakeID3D11Device::CheckFormatSupport(DXGI_FORMAT Format, UINT * pFormatSupport)
{
	return realDevice->CheckFormatSupport(Format, pFormatSupport);
}

HRESULT __stdcall FakeID3D11Device::CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT * pNumQualityLevels)
{
	return realDevice->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
}

void __stdcall FakeID3D11Device::CheckCounterInfo(D3D11_COUNTER_INFO * pCounterInfo)
{
	realDevice->CheckCounterInfo(pCounterInfo);
}

HRESULT __stdcall FakeID3D11Device::CheckCounter(const D3D11_COUNTER_DESC * pDesc, D3D11_COUNTER_TYPE * pType, UINT * pActiveCounters, LPSTR szName, UINT * pNameLength, LPSTR szUnits, UINT * pUnitsLength, LPSTR szDescription, UINT * pDescriptionLength)
{
	return realDevice->CheckCounter(pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength, szDescription, pDescriptionLength);
}

HRESULT __stdcall FakeID3D11Device::CheckFeatureSupport(D3D11_FEATURE Feature, void * pFeatureSupportData, UINT FeatureSupportDataSize)
{
	return realDevice->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
}

HRESULT __stdcall FakeID3D11Device::GetPrivateData(REFGUID guid, UINT * pDataSize, void * pData)
{
	return realDevice->GetPrivateData(guid, pDataSize, pData);
}

HRESULT __stdcall FakeID3D11Device::SetPrivateData(REFGUID guid, UINT DataSize, const void * pData)
{
	return realDevice->SetPrivateData(guid, DataSize, pData);
}

HRESULT __stdcall FakeID3D11Device::SetPrivateDataInterface(REFGUID guid, const IUnknown * pData)
{
	return realDevice->SetPrivateDataInterface(guid, pData);
}

D3D_FEATURE_LEVEL __stdcall FakeID3D11Device::GetFeatureLevel(void)
{
	return realDevice->GetFeatureLevel();
}

UINT __stdcall FakeID3D11Device::GetCreationFlags(void)
{
	return realDevice->GetCreationFlags();
}

HRESULT __stdcall FakeID3D11Device::GetDeviceRemovedReason(void)
{
	return realDevice->GetDeviceRemovedReason();
}

void __stdcall FakeID3D11Device::GetImmediateContext(ID3D11DeviceContext ** ppImmediateContext)
{
	immediateContext->AddRef();
	*ppImmediateContext = immediateContext;
}

HRESULT __stdcall FakeID3D11Device::SetExceptionMode(UINT RaiseFlags)
{
	return realDevice->SetExceptionMode(RaiseFlags);
}

UINT __stdcall FakeID3D11Device::GetExceptionMode(void)
{
	return realDevice->GetExceptionMode();
}

void __stdcall FakeID3D11Device::GetImmediateContext1(ID3D11DeviceContext1 ** ppImmediateContext)
{
	immediateContext->AddRef();
	*ppImmediateContext = immediateContext;
}

HRESULT __stdcall FakeID3D11Device::CreateDeferredContext1(UINT ContextFlags, ID3D11DeviceContext1 ** ppDeferredContext)
{
	HRESULT result = realDevice->CreateDeferredContext1(ContextFlags, ppDeferredContext);
	if (result == S_OK)
	{
		FakeID3D11DeviceContext* fake = new FakeID3D11DeviceContext(*ppDeferredContext, this);
		*ppDeferredContext = fake;
		++info.numberOfCreatedContexts;
	}
	return result;
}

HRESULT __stdcall FakeID3D11Device::CreateBlendState1(const D3D11_BLEND_DESC1 * pBlendStateDesc, ID3D11BlendState1 ** ppBlendState)
{
	return realDevice->CreateBlendState1(pBlendStateDesc, ppBlendState);
}

HRESULT __stdcall FakeID3D11Device::CreateRasterizerState1(const D3D11_RASTERIZER_DESC1 * pRasterizerDesc, ID3D11RasterizerState1 ** ppRasterizerState)
{
	return realDevice->CreateRasterizerState1(pRasterizerDesc, ppRasterizerState);
}

HRESULT __stdcall FakeID3D11Device::CreateDeviceContextState(UINT Flags, const D3D_FEATURE_LEVEL * pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, REFIID EmulatedInterface, D3D_FEATURE_LEVEL * pChosenFeatureLevel, ID3DDeviceContextState ** ppContextState)
{
	return realDevice->CreateDeviceContextState(Flags, pFeatureLevels, FeatureLevels, SDKVersion, EmulatedInterface, pChosenFeatureLevel, ppContextState);
}

HRESULT __stdcall FakeID3D11Device::OpenSharedResource1(HANDLE hResource, REFIID returnedInterface, void ** ppResource)
{
	return realDevice->OpenSharedResource1(hResource, returnedInterface, ppResource);
}

HRESULT __stdcall FakeID3D11Device::OpenSharedResourceByName(LPCWSTR lpName, DWORD dwDesiredAccess, REFIID returnedInterface, void ** ppResource)
{
	return realDevice->OpenSharedResourceByName(lpName, dwDesiredAccess, returnedInterface, ppResource);
}

void __stdcall FakeID3D11Device::GetImmediateContext2(ID3D11DeviceContext2 ** ppImmediateContext)
{
	immediateContext->AddRef();
	*ppImmediateContext = immediateContext;
}

HRESULT __stdcall FakeID3D11Device::CreateDeferredContext2(UINT ContextFlags, ID3D11DeviceContext2 ** ppDeferredContext)
{
	HRESULT result = realDevice->CreateDeferredContext2(ContextFlags, ppDeferredContext);
	if (result == S_OK)
	{
		FakeID3D11DeviceContext* fake = new FakeID3D11DeviceContext(*ppDeferredContext, this);
		*ppDeferredContext = fake;
		++info.numberOfCreatedContexts;
	}
	return result;
}

void __stdcall FakeID3D11Device::GetResourceTiling(ID3D11Resource * pTiledResource, UINT * pNumTilesForEntireResource, D3D11_PACKED_MIP_DESC * pPackedMipDesc, D3D11_TILE_SHAPE * pStandardTileShapeForNonPackedMips, UINT * pNumSubresourceTilings, UINT FirstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING * pSubresourceTilingsForNonPackedMips)
{
	realDevice->GetResourceTiling(pTiledResource, pNumTilesForEntireResource, pPackedMipDesc, pStandardTileShapeForNonPackedMips, pNumSubresourceTilings, FirstSubresourceTilingToGet, pSubresourceTilingsForNonPackedMips);
}

HRESULT __stdcall FakeID3D11Device::CheckMultisampleQualityLevels1(DXGI_FORMAT Format, UINT SampleCount, UINT Flags, UINT * pNumQualityLevels)
{
	return realDevice->CheckMultisampleQualityLevels1(Format, SampleCount, Flags, pNumQualityLevels);
}

HRESULT __stdcall FakeID3D11Device::CreateTexture2D1(const D3D11_TEXTURE2D_DESC1 * pDesc1, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture2D1 ** ppTexture2D)
{
	return realDevice->CreateTexture2D1(pDesc1, pInitialData, ppTexture2D);
}

HRESULT __stdcall FakeID3D11Device::CreateTexture3D1(const D3D11_TEXTURE3D_DESC1 * pDesc1, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture3D1 ** ppTexture3D)
{
	return realDevice->CreateTexture3D1(pDesc1, pInitialData, ppTexture3D);
}

HRESULT __stdcall FakeID3D11Device::CreateRasterizerState2(const D3D11_RASTERIZER_DESC2 * pRasterizerDesc, ID3D11RasterizerState2 ** ppRasterizerState)
{
	return realDevice->CreateRasterizerState2(pRasterizerDesc, ppRasterizerState);
}

HRESULT __stdcall FakeID3D11Device::CreateShaderResourceView1(ID3D11Resource * pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC1 * pDesc1, ID3D11ShaderResourceView1 ** ppSRView1)
{
	return realDevice->CreateShaderResourceView1(pResource, pDesc1, ppSRView1);
}

HRESULT __stdcall FakeID3D11Device::CreateUnorderedAccessView1(ID3D11Resource * pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC1 * pDesc1, ID3D11UnorderedAccessView1 ** ppUAView1)
{
	return realDevice->CreateUnorderedAccessView1(pResource, pDesc1, ppUAView1);
}

HRESULT __stdcall FakeID3D11Device::CreateRenderTargetView1(ID3D11Resource * pResource, const D3D11_RENDER_TARGET_VIEW_DESC1 * pDesc1, ID3D11RenderTargetView1 ** ppRTView1)
{
	return realDevice->CreateRenderTargetView1(pResource, pDesc1, ppRTView1);
}

HRESULT __stdcall FakeID3D11Device::CreateQuery1(const D3D11_QUERY_DESC1 * pQueryDesc1, ID3D11Query1 ** ppQuery1)
{
	return realDevice->CreateQuery1(pQueryDesc1, ppQuery1);
}

void __stdcall FakeID3D11Device::GetImmediateContext3(ID3D11DeviceContext3 ** ppImmediateContext)
{
	immediateContext->AddRef();
	*ppImmediateContext = immediateContext;
}

HRESULT __stdcall FakeID3D11Device::CreateDeferredContext3(UINT ContextFlags, ID3D11DeviceContext3 ** ppDeferredContext)
{
	HRESULT result = realDevice->CreateDeferredContext3(ContextFlags, ppDeferredContext);
	if (result == S_OK)
	{
		FakeID3D11DeviceContext* fake = new FakeID3D11DeviceContext(*ppDeferredContext, this);
		*ppDeferredContext = fake;
		++info.numberOfCreatedContexts;
	}
	return result;
}

void __stdcall FakeID3D11Device::WriteToSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	realDevice->WriteToSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void __stdcall FakeID3D11Device::ReadFromSubresource(void * pDstData, UINT DstRowPitch, UINT DstDepthPitch, ID3D11Resource * pSrcResource, UINT SrcSubresource, const D3D11_BOX * pSrcBox)
{
	realDevice->ReadFromSubresource(pDstData, DstRowPitch, DstDepthPitch, pSrcResource, SrcSubresource, pSrcBox);
}

HRESULT __stdcall FakeID3D11Device::RegisterDeviceRemovedEvent(HANDLE hEvent, DWORD * pdwCookie)
{
	return realDevice->RegisterDeviceRemovedEvent(hEvent, pdwCookie);
}

void __stdcall FakeID3D11Device::UnregisterDeviceRemoved(DWORD dwCookie)
{
	realDevice->UnregisterDeviceRemoved(dwCookie);
}

HRESULT __stdcall FakeID3D11Device::OpenSharedFence(HANDLE hFence, REFIID ReturnedInterface, void ** ppFence)
{
	return realDevice->OpenSharedFence(hFence, ReturnedInterface, ppFence);
}

HRESULT __stdcall FakeID3D11Device::CreateFence(UINT64 InitialValue, D3D11_FENCE_FLAG Flags, REFIID ReturnedInterface, void ** ppFence)
{
	return realDevice->CreateFence(InitialValue, Flags, ReturnedInterface, ppFence);
}