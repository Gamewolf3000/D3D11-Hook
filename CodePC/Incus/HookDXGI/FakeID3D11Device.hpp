#pragma once

#include <d3d11_4.h>
#include <utility>
#include <cstdint>

class FakeID3D11DeviceContext;

struct DeviceInfo
{
	std::uint_fast32_t numberOfCreatedContexts = 0;
	std::uint_fast32_t numberOfCreatedVertexShaders = 0;
	std::uint_fast32_t numberOfCreatedHullShaders = 0;
	std::uint_fast32_t numberOfCreatedDomainShaders = 0;
	std::uint_fast32_t numberOfCreatedGeometryShaders = 0;
	std::uint_fast32_t numberOfCreatedPixelShaders = 0;
	std::uint_fast32_t numberOfCreatedComputeShaders = 0;
	std::uint_fast32_t numberOfCreatedRasterizerStates = 0;
};

class FakeID3D11Device : public ID3D11Device5
{
private:
	ID3D11Device5* realDevice;
	FakeID3D11DeviceContext* immediateContext = nullptr;

public:
	FakeID3D11Device(ID3D11Device* real);
	virtual ~FakeID3D11Device() {};
	void SetImmediateContext(FakeID3D11DeviceContext* context);
	ID3D11Device5* GetReal();

	DeviceInfo info;
	
	// Inherited via ID3D11Device5 70
	template<typename Q>
	HRESULT __stdcall QueryInterface(Q ** pp) override;
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void ** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;

	virtual HRESULT __stdcall CreateBuffer(const D3D11_BUFFER_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Buffer ** ppBuffer) override;

	virtual HRESULT __stdcall CreateTexture1D(const D3D11_TEXTURE1D_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture1D ** ppTexture1D) override;

	virtual HRESULT __stdcall CreateTexture2D(const D3D11_TEXTURE2D_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture2D ** ppTexture2D) override;

	virtual HRESULT __stdcall CreateTexture3D(const D3D11_TEXTURE3D_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture3D ** ppTexture3D) override;

	virtual HRESULT __stdcall CreateShaderResourceView(ID3D11Resource * pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC * pDesc, ID3D11ShaderResourceView ** ppSRView) override;

	virtual HRESULT __stdcall CreateUnorderedAccessView(ID3D11Resource * pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC * pDesc, ID3D11UnorderedAccessView ** ppUAView) override;

	virtual HRESULT __stdcall CreateRenderTargetView(ID3D11Resource * pResource, const D3D11_RENDER_TARGET_VIEW_DESC * pDesc, ID3D11RenderTargetView ** ppRTView) override;

	virtual HRESULT __stdcall CreateDepthStencilView(ID3D11Resource * pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC * pDesc, ID3D11DepthStencilView ** ppDepthStencilView) override;

	virtual HRESULT __stdcall CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC * pInputElementDescs, UINT NumElements, const void * pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout ** ppInputLayout) override;

	virtual HRESULT __stdcall CreateVertexShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11VertexShader ** ppVertexShader) override;

	virtual HRESULT __stdcall CreateGeometryShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11GeometryShader ** ppGeometryShader) override;

	virtual HRESULT __stdcall CreateGeometryShaderWithStreamOutput(const void * pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY * pSODeclaration, UINT NumEntries, const UINT * pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage * pClassLinkage, ID3D11GeometryShader ** ppGeometryShader) override;

	virtual HRESULT __stdcall CreatePixelShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11PixelShader ** ppPixelShader) override;

	virtual HRESULT __stdcall CreateHullShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11HullShader ** ppHullShader) override;

	virtual HRESULT __stdcall CreateDomainShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11DomainShader ** ppDomainShader) override;

	virtual HRESULT __stdcall CreateComputeShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11ComputeShader ** ppComputeShader) override;

	virtual HRESULT __stdcall CreateClassLinkage(ID3D11ClassLinkage ** ppLinkage) override;

	virtual HRESULT __stdcall CreateBlendState(const D3D11_BLEND_DESC * pBlendStateDesc, ID3D11BlendState ** ppBlendState) override;

	virtual HRESULT __stdcall CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC * pDepthStencilDesc, ID3D11DepthStencilState ** ppDepthStencilState) override;

	virtual HRESULT __stdcall CreateRasterizerState(const D3D11_RASTERIZER_DESC * pRasterizerDesc, ID3D11RasterizerState ** ppRasterizerState) override;

	virtual HRESULT __stdcall CreateSamplerState(const D3D11_SAMPLER_DESC * pSamplerDesc, ID3D11SamplerState ** ppSamplerState) override;

	virtual HRESULT __stdcall CreateQuery(const D3D11_QUERY_DESC * pQueryDesc, ID3D11Query ** ppQuery) override;

	virtual HRESULT __stdcall CreatePredicate(const D3D11_QUERY_DESC * pPredicateDesc, ID3D11Predicate ** ppPredicate) override;

	virtual HRESULT __stdcall CreateCounter(const D3D11_COUNTER_DESC * pCounterDesc, ID3D11Counter ** ppCounter) override;

	virtual HRESULT __stdcall CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext ** ppDeferredContext) override;

	virtual HRESULT __stdcall OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void ** ppResource) override;

	virtual HRESULT __stdcall CheckFormatSupport(DXGI_FORMAT Format, UINT * pFormatSupport) override;

	virtual HRESULT __stdcall CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT * pNumQualityLevels) override;

	virtual void __stdcall CheckCounterInfo(D3D11_COUNTER_INFO * pCounterInfo) override;

	virtual HRESULT __stdcall CheckCounter(const D3D11_COUNTER_DESC * pDesc, D3D11_COUNTER_TYPE * pType, UINT * pActiveCounters, LPSTR szName, UINT * pNameLength, LPSTR szUnits, UINT * pUnitsLength, LPSTR szDescription, UINT * pDescriptionLength) override;

	virtual HRESULT __stdcall CheckFeatureSupport(D3D11_FEATURE Feature, void * pFeatureSupportData, UINT FeatureSupportDataSize) override;

	virtual HRESULT __stdcall GetPrivateData(REFGUID guid, UINT * pDataSize, void * pData) override;

	virtual HRESULT __stdcall SetPrivateData(REFGUID guid, UINT DataSize, const void * pData) override;

	virtual HRESULT __stdcall SetPrivateDataInterface(REFGUID guid, const IUnknown * pData) override;

	virtual D3D_FEATURE_LEVEL __stdcall GetFeatureLevel(void) override;

	virtual UINT __stdcall GetCreationFlags(void) override;

	virtual HRESULT __stdcall GetDeviceRemovedReason(void) override;

	virtual void __stdcall GetImmediateContext(ID3D11DeviceContext ** ppImmediateContext) override;

	virtual HRESULT __stdcall SetExceptionMode(UINT RaiseFlags) override;

	virtual UINT __stdcall GetExceptionMode(void) override;

	virtual void __stdcall GetImmediateContext1(ID3D11DeviceContext1 ** ppImmediateContext) override;

	virtual HRESULT __stdcall CreateDeferredContext1(UINT ContextFlags, ID3D11DeviceContext1 ** ppDeferredContext) override;

	virtual HRESULT __stdcall CreateBlendState1(const D3D11_BLEND_DESC1 * pBlendStateDesc, ID3D11BlendState1 ** ppBlendState) override;

	virtual HRESULT __stdcall CreateRasterizerState1(const D3D11_RASTERIZER_DESC1 * pRasterizerDesc, ID3D11RasterizerState1 ** ppRasterizerState) override;

	virtual HRESULT __stdcall CreateDeviceContextState(UINT Flags, const D3D_FEATURE_LEVEL * pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, REFIID EmulatedInterface, D3D_FEATURE_LEVEL * pChosenFeatureLevel, ID3DDeviceContextState ** ppContextState) override;

	virtual HRESULT __stdcall OpenSharedResource1(HANDLE hResource, REFIID returnedInterface, void ** ppResource) override;

	virtual HRESULT __stdcall OpenSharedResourceByName(LPCWSTR lpName, DWORD dwDesiredAccess, REFIID returnedInterface, void ** ppResource) override;

	virtual void __stdcall GetImmediateContext2(ID3D11DeviceContext2 ** ppImmediateContext) override;

	virtual HRESULT __stdcall CreateDeferredContext2(UINT ContextFlags, ID3D11DeviceContext2 ** ppDeferredContext) override;

	virtual void __stdcall GetResourceTiling(ID3D11Resource * pTiledResource, UINT * pNumTilesForEntireResource, D3D11_PACKED_MIP_DESC * pPackedMipDesc, D3D11_TILE_SHAPE * pStandardTileShapeForNonPackedMips, UINT * pNumSubresourceTilings, UINT FirstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING * pSubresourceTilingsForNonPackedMips) override;

	virtual HRESULT __stdcall CheckMultisampleQualityLevels1(DXGI_FORMAT Format, UINT SampleCount, UINT Flags, UINT * pNumQualityLevels) override;

	virtual HRESULT __stdcall CreateTexture2D1(const D3D11_TEXTURE2D_DESC1 * pDesc1, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture2D1 ** ppTexture2D) override;

	virtual HRESULT __stdcall CreateTexture3D1(const D3D11_TEXTURE3D_DESC1 * pDesc1, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture3D1 ** ppTexture3D) override;

	virtual HRESULT __stdcall CreateRasterizerState2(const D3D11_RASTERIZER_DESC2 * pRasterizerDesc, ID3D11RasterizerState2 ** ppRasterizerState) override;

	virtual HRESULT __stdcall CreateShaderResourceView1(ID3D11Resource * pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC1 * pDesc1, ID3D11ShaderResourceView1 ** ppSRView1) override;

	virtual HRESULT __stdcall CreateUnorderedAccessView1(ID3D11Resource * pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC1 * pDesc1, ID3D11UnorderedAccessView1 ** ppUAView1) override;

	virtual HRESULT __stdcall CreateRenderTargetView1(ID3D11Resource * pResource, const D3D11_RENDER_TARGET_VIEW_DESC1 * pDesc1, ID3D11RenderTargetView1 ** ppRTView1) override;

	virtual HRESULT __stdcall CreateQuery1(const D3D11_QUERY_DESC1 * pQueryDesc1, ID3D11Query1 ** ppQuery1) override;

	virtual void __stdcall GetImmediateContext3(ID3D11DeviceContext3 ** ppImmediateContext) override;

	virtual HRESULT __stdcall CreateDeferredContext3(UINT ContextFlags, ID3D11DeviceContext3 ** ppDeferredContext) override;

	virtual void __stdcall WriteToSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) override;

	virtual void __stdcall ReadFromSubresource(void * pDstData, UINT DstRowPitch, UINT DstDepthPitch, ID3D11Resource * pSrcResource, UINT SrcSubresource, const D3D11_BOX * pSrcBox) override;

	virtual HRESULT __stdcall RegisterDeviceRemovedEvent(HANDLE hEvent, DWORD * pdwCookie) override;

	virtual void __stdcall UnregisterDeviceRemoved(DWORD dwCookie) override;

	virtual HRESULT __stdcall OpenSharedFence(HANDLE hFence, REFIID ReturnedInterface, void ** ppFence) override;

	virtual HRESULT __stdcall CreateFence(UINT64 InitialValue, D3D11_FENCE_FLAG Flags, REFIID ReturnedInterface, void ** ppFence) override;
	
};


template<typename Q>
inline HRESULT __stdcall FakeID3D11Device::QueryInterface(_COM_Outptr_ Q ** pp)
{
	return QueryInterface(__uuidof(Q), (void **)pp);
}
