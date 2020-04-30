#pragma once

#include <d3d11_4.h>

#include <utility>
#include <cstdint>

class FakeID3D11Device;

struct DeviceContextInfo
{
	std::uint_fast32_t numberOfVertexShadersSet = 0;
	std::uint_fast32_t numberOfHullShadersSet = 0;
	std::uint_fast32_t numberOfDomainShadersSet = 0;
	std::uint_fast32_t numberOfGeometryShadersSet = 0;
	std::uint_fast32_t numberOfPixelShadersSet = 0;
	std::uint_fast32_t numberOfComputeShadersSet = 0;
	std::uint_fast32_t numberOfCreatedRasterizerStates = 0;
};

class FakeID3D11DeviceContext : public ID3D11DeviceContext4
{
private:
	ID3D11DeviceContext4* realDeviceContext;
	FakeID3D11Device* creatorDevice;

public:
	FakeID3D11DeviceContext(ID3D11DeviceContext* real, FakeID3D11Device* creator);

	// Inherited via ID3D11DeviceContext4 (149 + 1)
	template<typename Q>
	HRESULT __stdcall QueryInterface(Q ** pp);


	/*0*/virtual HRESULT __stdcall QueryInterface(REFIID riid, void ** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;
	virtual void __stdcall GetDevice(ID3D11Device ** ppDevice) override;
	virtual HRESULT __stdcall GetPrivateData(REFGUID guid, UINT * pDataSize, void * pData) override;
	virtual HRESULT __stdcall SetPrivateData(REFGUID guid, UINT DataSize, const void * pData) override;
	virtual HRESULT __stdcall SetPrivateDataInterface(REFGUID guid, const IUnknown * pData) override;
	virtual void __stdcall VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers) override;
	virtual void __stdcall PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews) override;
	/*10*/virtual void __stdcall PSSetShader(ID3D11PixelShader * pPixelShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances) override;
	virtual void __stdcall PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers) override;
	virtual void __stdcall VSSetShader(ID3D11VertexShader * pVertexShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances) override;
	virtual void __stdcall DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) override;
	virtual void __stdcall Draw(UINT VertexCount, UINT StartVertexLocation) override;
	virtual HRESULT __stdcall Map(ID3D11Resource * pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE * pMappedResource) override;
	virtual void __stdcall Unmap(ID3D11Resource * pResource, UINT Subresource) override;
	virtual void __stdcall PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers) override;
	virtual void __stdcall IASetInputLayout(ID3D11InputLayout * pInputLayout) override;
	virtual void __stdcall IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppVertexBuffers, const UINT * pStrides, const UINT * pOffsets) override;
	/*20*/virtual void __stdcall IASetIndexBuffer(ID3D11Buffer * pIndexBuffer, DXGI_FORMAT Format, UINT Offset) override;
	virtual void __stdcall DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation) override;
	virtual void __stdcall DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation) override;
	virtual void __stdcall GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers) override;
	virtual void __stdcall GSSetShader(ID3D11GeometryShader * pShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances) override;
	virtual void __stdcall IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) override;
	virtual void __stdcall VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews) override;
	virtual void __stdcall VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers) override;
	virtual void __stdcall Begin(ID3D11Asynchronous * pAsync) override;
	virtual void __stdcall End(ID3D11Asynchronous * pAsync) override;
	/*30*/virtual HRESULT __stdcall GetData(ID3D11Asynchronous * pAsync, void * pData, UINT DataSize, UINT GetDataFlags) override;
	virtual void __stdcall SetPredication(ID3D11Predicate * pPredicate, BOOL PredicateValue) override;
	virtual void __stdcall GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews) override;
	virtual void __stdcall GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers) override;
	virtual void __stdcall OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView * const * ppRenderTargetViews, ID3D11DepthStencilView * pDepthStencilView) override;
	virtual void __stdcall OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView * const * ppRenderTargetViews, ID3D11DepthStencilView * pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView * const * ppUnorderedAccessViews, const UINT * pUAVInitialCounts) override;
	virtual void __stdcall OMSetBlendState(ID3D11BlendState * pBlendState, const FLOAT BlendFactor[4], UINT SampleMask) override;
	virtual void __stdcall OMSetDepthStencilState(ID3D11DepthStencilState * pDepthStencilState, UINT StencilRef) override;
	virtual void __stdcall SOSetTargets(UINT NumBuffers, ID3D11Buffer * const * ppSOTargets, const UINT * pOffsets) override;
	virtual void __stdcall DrawAuto(void) override;
	/*40*/virtual void __stdcall DrawIndexedInstancedIndirect(ID3D11Buffer * pBufferForArgs, UINT AlignedByteOffsetForArgs) override;
	virtual void __stdcall DrawInstancedIndirect(ID3D11Buffer * pBufferForArgs, UINT AlignedByteOffsetForArgs) override;
	virtual void __stdcall Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ) override;
	virtual void __stdcall DispatchIndirect(ID3D11Buffer * pBufferForArgs, UINT AlignedByteOffsetForArgs) override;
	virtual void __stdcall RSSetState(ID3D11RasterizerState * pRasterizerState) override;
	virtual void __stdcall RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT * pViewports) override;
	virtual void __stdcall RSSetScissorRects(UINT NumRects, const D3D11_RECT * pRects) override;
	virtual void __stdcall CopySubresourceRegion(ID3D11Resource * pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource * pSrcResource, UINT SrcSubresource, const D3D11_BOX * pSrcBox) override;
	virtual void __stdcall CopyResource(ID3D11Resource * pDstResource, ID3D11Resource * pSrcResource) override;
	virtual void __stdcall UpdateSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) override;
	/*50*/virtual void __stdcall CopyStructureCount(ID3D11Buffer * pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView * pSrcView) override;
	virtual void __stdcall ClearRenderTargetView(ID3D11RenderTargetView * pRenderTargetView, const FLOAT ColorRGBA[4]) override;
	virtual void __stdcall ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView * pUnorderedAccessView, const UINT Values[4]) override;
	virtual void __stdcall ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView * pUnorderedAccessView, const FLOAT Values[4]) override;
	virtual void __stdcall ClearDepthStencilView(ID3D11DepthStencilView * pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil) override;
	virtual void __stdcall GenerateMips(ID3D11ShaderResourceView * pShaderResourceView) override;
	virtual void __stdcall SetResourceMinLOD(ID3D11Resource * pResource, FLOAT MinLOD) override;
	virtual FLOAT __stdcall GetResourceMinLOD(ID3D11Resource * pResource) override;
	virtual void __stdcall ResolveSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, ID3D11Resource * pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format) override;
	virtual void __stdcall ExecuteCommandList(ID3D11CommandList * pCommandList, BOOL RestoreContextState) override;
	/*60*/virtual void __stdcall HSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews) override;
	virtual void __stdcall HSSetShader(ID3D11HullShader * pHullShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances) override;
	virtual void __stdcall HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers) override;
	virtual void __stdcall HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers) override;
	virtual void __stdcall DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews) override;
	virtual void __stdcall DSSetShader(ID3D11DomainShader * pDomainShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances) override;
	virtual void __stdcall DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers) override;
	virtual void __stdcall DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers) override;
	virtual void __stdcall CSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews) override;
	virtual void __stdcall CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView * const * ppUnorderedAccessViews, const UINT * pUAVInitialCounts) override;
	/*70*/virtual void __stdcall CSSetShader(ID3D11ComputeShader * pComputeShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances) override;
	virtual void __stdcall CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers) override;
	virtual void __stdcall CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers) override;
	virtual void __stdcall VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers) override;
	virtual void __stdcall PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews) override;
	virtual void __stdcall PSGetShader(ID3D11PixelShader ** ppPixelShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances) override;
	virtual void __stdcall PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers) override;
	virtual void __stdcall VSGetShader(ID3D11VertexShader ** ppVertexShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances) override;
	virtual void __stdcall PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers) override;
	virtual void __stdcall IAGetInputLayout(ID3D11InputLayout ** ppInputLayout) override;
	/*80*/virtual void __stdcall IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppVertexBuffers, UINT * pStrides, UINT * pOffsets) override;
	virtual void __stdcall IAGetIndexBuffer(ID3D11Buffer ** pIndexBuffer, DXGI_FORMAT * Format, UINT * Offset) override;
	virtual void __stdcall GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers) override;
	virtual void __stdcall GSGetShader(ID3D11GeometryShader ** ppGeometryShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances) override;
	virtual void __stdcall IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY * pTopology) override;
	virtual void __stdcall VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews) override;
	virtual void __stdcall VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers) override;
	virtual void __stdcall GetPredication(ID3D11Predicate ** ppPredicate, BOOL * pPredicateValue) override;
	virtual void __stdcall GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews) override;
	virtual void __stdcall GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers) override;
	/*90*/virtual void __stdcall OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView ** ppRenderTargetViews, ID3D11DepthStencilView ** ppDepthStencilView) override;
	virtual void __stdcall OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView ** ppRenderTargetViews, ID3D11DepthStencilView ** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView ** ppUnorderedAccessViews) override;
	virtual void __stdcall OMGetBlendState(ID3D11BlendState ** ppBlendState, FLOAT BlendFactor[4], UINT * pSampleMask) override;
	virtual void __stdcall OMGetDepthStencilState(ID3D11DepthStencilState ** ppDepthStencilState, UINT * pStencilRef) override;
	virtual void __stdcall SOGetTargets(UINT NumBuffers, ID3D11Buffer ** ppSOTargets) override;
	virtual void __stdcall RSGetState(ID3D11RasterizerState ** ppRasterizerState) override;
	virtual void __stdcall RSGetViewports(UINT * pNumViewports, D3D11_VIEWPORT * pViewports) override;
	virtual void __stdcall RSGetScissorRects(UINT * pNumRects, D3D11_RECT * pRects) override;
	virtual void __stdcall HSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews) override;
	virtual void __stdcall HSGetShader(ID3D11HullShader ** ppHullShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances) override;
	/*100*/virtual void __stdcall HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers) override;
	virtual void __stdcall HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers) override;
	virtual void __stdcall DSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews) override;
	virtual void __stdcall DSGetShader(ID3D11DomainShader ** ppDomainShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances) override;
	virtual void __stdcall DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers) override;
	virtual void __stdcall DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers) override;
	virtual void __stdcall CSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews) override;
	virtual void __stdcall CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView ** ppUnorderedAccessViews) override;
	virtual void __stdcall CSGetShader(ID3D11ComputeShader ** ppComputeShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances) override;
	virtual void __stdcall CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers) override;
	/*110*/virtual void __stdcall CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers) override;
	virtual void __stdcall ClearState(void) override;
	virtual void __stdcall Flush(void) override;
	virtual D3D11_DEVICE_CONTEXT_TYPE __stdcall GetType(void) override;
	virtual UINT __stdcall GetContextFlags(void) override;
	virtual HRESULT __stdcall FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList ** ppCommandList) override;
	virtual void __stdcall CopySubresourceRegion1(ID3D11Resource * pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource * pSrcResource, UINT SrcSubresource, const D3D11_BOX * pSrcBox, UINT CopyFlags) override;
	virtual void __stdcall UpdateSubresource1(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch, UINT CopyFlags) override;
	virtual void __stdcall DiscardResource(ID3D11Resource * pResource) override;
	virtual void __stdcall DiscardView(ID3D11View * pResourceView) override;
	/*120*/virtual void __stdcall VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants) override;
	virtual void __stdcall HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants) override;
	virtual void __stdcall DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants) override;
	virtual void __stdcall GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants) override;
	virtual void __stdcall PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants) override;
	virtual void __stdcall CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants) override;
	virtual void __stdcall VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants) override;
	virtual void __stdcall HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants) override;
	virtual void __stdcall DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants) override;
	virtual void __stdcall GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants) override;
	/*130*/virtual void __stdcall PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants) override;
	virtual void __stdcall CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants) override;
	virtual void __stdcall SwapDeviceContextState(ID3DDeviceContextState * pState, ID3DDeviceContextState ** ppPreviousState) override;
	virtual void __stdcall ClearView(ID3D11View * pView, const FLOAT Color[4], const D3D11_RECT * pRect, UINT NumRects) override;
	virtual void __stdcall DiscardView1(ID3D11View * pResourceView, const D3D11_RECT * pRects, UINT NumRects) override;
	virtual HRESULT __stdcall UpdateTileMappings(ID3D11Resource * pTiledResource, UINT NumTiledResourceRegions, const D3D11_TILED_RESOURCE_COORDINATE * pTiledResourceRegionStartCoordinates, const D3D11_TILE_REGION_SIZE * pTiledResourceRegionSizes, ID3D11Buffer * pTilePool, UINT NumRanges, const UINT * pRangeFlags, const UINT * pTilePoolStartOffsets, const UINT * pRangeTileCounts, UINT Flags) override;
	virtual HRESULT __stdcall CopyTileMappings(ID3D11Resource * pDestTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pDestRegionStartCoordinate, ID3D11Resource * pSourceTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pSourceRegionStartCoordinate, const D3D11_TILE_REGION_SIZE * pTileRegionSize, UINT Flags) override;
	virtual void __stdcall CopyTiles(ID3D11Resource * pTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE * pTileRegionSize, ID3D11Buffer * pBuffer, UINT64 BufferStartOffsetInBytes, UINT Flags) override;
	virtual void __stdcall UpdateTiles(ID3D11Resource * pDestTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pDestTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE * pDestTileRegionSize, const void * pSourceTileData, UINT Flags) override;
	virtual HRESULT __stdcall ResizeTilePool(ID3D11Buffer * pTilePool, UINT64 NewSizeInBytes) override;
	/*140*/virtual void __stdcall TiledResourceBarrier(ID3D11DeviceChild * pTiledResourceOrViewAccessBeforeBarrier, ID3D11DeviceChild * pTiledResourceOrViewAccessAfterBarrier) override;
	virtual BOOL __stdcall IsAnnotationEnabled(void) override;
	virtual void __stdcall SetMarkerInt(LPCWSTR pLabel, INT Data) override;
	virtual void __stdcall BeginEventInt(LPCWSTR pLabel, INT Data) override;
	virtual void __stdcall EndEvent(void) override;
	virtual void __stdcall Flush1(D3D11_CONTEXT_TYPE ContextType, HANDLE hEvent) override;
	virtual void __stdcall SetHardwareProtectionState(BOOL HwProtectionEnable) override;
	virtual void __stdcall GetHardwareProtectionState(BOOL * pHwProtectionEnable) override;
	virtual HRESULT __stdcall Signal(ID3D11Fence * pFence, UINT64 Value) override;
	virtual HRESULT __stdcall Wait(ID3D11Fence * pFence, UINT64 Value) override;
};

template<typename Q>
inline HRESULT __stdcall FakeID3D11DeviceContext::QueryInterface(Q ** pp)
{
	return QueryInterface(__uuidof(Q), (void **)pp);
}
