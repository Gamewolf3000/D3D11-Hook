#include "FakeID3D11DeviceContext.h"

HRESULT __stdcall FakeID3D11DeviceContext::QueryInterface(REFIID riid, void ** ppvObject)
{
	return HRESULT __stdcall();
}

ULONG __stdcall FakeID3D11DeviceContext::AddRef(void)
{
	return 0;
}

ULONG __stdcall FakeID3D11DeviceContext::Release(void)
{
	return 0;
}

void __stdcall FakeID3D11DeviceContext::GetDevice(ID3D11Device ** ppDevice)
{
	return void __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::GetPrivateData(REFGUID guid, UINT * pDataSize, void * pData)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::SetPrivateData(REFGUID guid, UINT DataSize, const void * pData)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::SetPrivateDataInterface(REFGUID guid, const IUnknown * pData)
{
	return HRESULT __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSSetShader(ID3D11PixelShader * pPixelShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSSetShader(ID3D11VertexShader * pVertexShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::Draw(UINT VertexCount, UINT StartVertexLocation)
{
	return void __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::Map(ID3D11Resource * pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE * pMappedResource)
{
	return HRESULT __stdcall();
}

void __stdcall FakeID3D11DeviceContext::Unmap(ID3D11Resource * pResource, UINT Subresource)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::IASetInputLayout(ID3D11InputLayout * pInputLayout)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppVertexBuffers, const UINT * pStrides, const UINT * pOffsets)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::IASetIndexBuffer(ID3D11Buffer * pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSSetShader(ID3D11GeometryShader * pShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::Begin(ID3D11Asynchronous * pAsync)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::End(ID3D11Asynchronous * pAsync)
{
	return void __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::GetData(ID3D11Asynchronous * pAsync, void * pData, UINT DataSize, UINT GetDataFlags)
{
	return HRESULT __stdcall();
}

void __stdcall FakeID3D11DeviceContext::SetPredication(ID3D11Predicate * pPredicate, BOOL PredicateValue)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView * const * ppRenderTargetViews, ID3D11DepthStencilView * pDepthStencilView)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView * const * ppRenderTargetViews, ID3D11DepthStencilView * pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView * const * ppUnorderedAccessViews, const UINT * pUAVInitialCounts)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::OMSetBlendState(ID3D11BlendState * pBlendState, const FLOAT BlendFactor[4], UINT SampleMask)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::OMSetDepthStencilState(ID3D11DepthStencilState * pDepthStencilState, UINT StencilRef)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::SOSetTargets(UINT NumBuffers, ID3D11Buffer * const * ppSOTargets, const UINT * pOffsets)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DrawAuto(void)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DrawIndexedInstancedIndirect(ID3D11Buffer * pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DrawInstancedIndirect(ID3D11Buffer * pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DispatchIndirect(ID3D11Buffer * pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::RSSetState(ID3D11RasterizerState * pRasterizerState)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT * pViewports)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::RSSetScissorRects(UINT NumRects, const D3D11_RECT * pRects)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CopySubresourceRegion(ID3D11Resource * pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource * pSrcResource, UINT SrcSubresource, const D3D11_BOX * pSrcBox)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CopyResource(ID3D11Resource * pDstResource, ID3D11Resource * pSrcResource)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::UpdateSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CopyStructureCount(ID3D11Buffer * pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView * pSrcView)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView * pRenderTargetView, const FLOAT ColorRGBA[4])
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView * pUnorderedAccessView, const UINT Values[4])
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView * pUnorderedAccessView, const FLOAT Values[4])
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView * pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GenerateMips(ID3D11ShaderResourceView * pShaderResourceView)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::SetResourceMinLOD(ID3D11Resource * pResource, FLOAT MinLOD)
{
	return void __stdcall();
}

FLOAT __stdcall FakeID3D11DeviceContext::GetResourceMinLOD(ID3D11Resource * pResource)
{
	return FLOAT __stdcall();
}

void __stdcall FakeID3D11DeviceContext::ResolveSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, ID3D11Resource * pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::ExecuteCommandList(ID3D11CommandList * pCommandList, BOOL RestoreContextState)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSSetShader(ID3D11HullShader * pHullShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSSetShader(ID3D11DomainShader * pDomainShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView * const * ppUnorderedAccessViews, const UINT * pUAVInitialCounts)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSSetShader(ID3D11ComputeShader * pComputeShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSGetShader(ID3D11PixelShader ** ppPixelShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSGetShader(ID3D11VertexShader ** ppVertexShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::IAGetInputLayout(ID3D11InputLayout ** ppInputLayout)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppVertexBuffers, UINT * pStrides, UINT * pOffsets)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::IAGetIndexBuffer(ID3D11Buffer ** pIndexBuffer, DXGI_FORMAT * Format, UINT * Offset)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSGetShader(ID3D11GeometryShader ** ppGeometryShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY * pTopology)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GetPredication(ID3D11Predicate ** ppPredicate, BOOL * pPredicateValue)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView ** ppRenderTargetViews, ID3D11DepthStencilView ** ppDepthStencilView)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView ** ppRenderTargetViews, ID3D11DepthStencilView ** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView ** ppUnorderedAccessViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::OMGetBlendState(ID3D11BlendState ** ppBlendState, FLOAT BlendFactor[4], UINT * pSampleMask)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::OMGetDepthStencilState(ID3D11DepthStencilState ** ppDepthStencilState, UINT * pStencilRef)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::SOGetTargets(UINT NumBuffers, ID3D11Buffer ** ppSOTargets)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::RSGetState(ID3D11RasterizerState ** ppRasterizerState)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::RSGetViewports(UINT * pNumViewports, D3D11_VIEWPORT * pViewports)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::RSGetScissorRects(UINT * pNumRects, D3D11_RECT * pRects)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSGetShader(ID3D11HullShader ** ppHullShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSGetShader(ID3D11DomainShader ** ppDomainShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView ** ppUnorderedAccessViews)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSGetShader(ID3D11ComputeShader ** ppComputeShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::ClearState(void)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::Flush(void)
{
	return void __stdcall();
}

D3D11_DEVICE_CONTEXT_TYPE __stdcall FakeID3D11DeviceContext::GetType(void)
{
	return D3D11_DEVICE_CONTEXT_TYPE __stdcall();
}

UINT __stdcall FakeID3D11DeviceContext::GetContextFlags(void)
{
	return 0;
}

HRESULT __stdcall FakeID3D11DeviceContext::FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList ** ppCommandList)
{
	return HRESULT __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CopySubresourceRegion1(ID3D11Resource * pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource * pSrcResource, UINT SrcSubresource, const D3D11_BOX * pSrcBox, UINT CopyFlags)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::UpdateSubresource1(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch, UINT CopyFlags)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DiscardResource(ID3D11Resource * pResource)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DiscardView(ID3D11View * pResourceView)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::SwapDeviceContextState(ID3DDeviceContextState * pState, ID3DDeviceContextState ** ppPreviousState)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::ClearView(ID3D11View * pView, const FLOAT Color[4], const D3D11_RECT * pRect, UINT NumRects)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::DiscardView1(ID3D11View * pResourceView, const D3D11_RECT * pRects, UINT NumRects)
{
	return void __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::UpdateTileMappings(ID3D11Resource * pTiledResource, UINT NumTiledResourceRegions, const D3D11_TILED_RESOURCE_COORDINATE * pTiledResourceRegionStartCoordinates, const D3D11_TILE_REGION_SIZE * pTiledResourceRegionSizes, ID3D11Buffer * pTilePool, UINT NumRanges, const UINT * pRangeFlags, const UINT * pTilePoolStartOffsets, const UINT * pRangeTileCounts, UINT Flags)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::CopyTileMappings(ID3D11Resource * pDestTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pDestRegionStartCoordinate, ID3D11Resource * pSourceTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pSourceRegionStartCoordinate, const D3D11_TILE_REGION_SIZE * pTileRegionSize, UINT Flags)
{
	return HRESULT __stdcall();
}

void __stdcall FakeID3D11DeviceContext::CopyTiles(ID3D11Resource * pTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE * pTileRegionSize, ID3D11Buffer * pBuffer, UINT64 BufferStartOffsetInBytes, UINT Flags)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::UpdateTiles(ID3D11Resource * pDestTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pDestTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE * pDestTileRegionSize, const void * pSourceTileData, UINT Flags)
{
	return void __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::ResizeTilePool(ID3D11Buffer * pTilePool, UINT64 NewSizeInBytes)
{
	return HRESULT __stdcall();
}

void __stdcall FakeID3D11DeviceContext::TiledResourceBarrier(ID3D11DeviceChild * pTiledResourceOrViewAccessBeforeBarrier, ID3D11DeviceChild * pTiledResourceOrViewAccessAfterBarrier)
{
	return void __stdcall();
}

BOOL __stdcall FakeID3D11DeviceContext::IsAnnotationEnabled(void)
{
	return 0;
}

void __stdcall FakeID3D11DeviceContext::SetMarkerInt(LPCWSTR pLabel, INT Data)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::BeginEventInt(LPCWSTR pLabel, INT Data)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::EndEvent(void)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::Flush1(D3D11_CONTEXT_TYPE ContextType, HANDLE hEvent)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::SetHardwareProtectionState(BOOL HwProtectionEnable)
{
	return void __stdcall();
}

void __stdcall FakeID3D11DeviceContext::GetHardwareProtectionState(BOOL * pHwProtectionEnable)
{
	return void __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::Signal(ID3D11Fence * pFence, UINT64 Value)
{
	return HRESULT __stdcall();
}

HRESULT __stdcall FakeID3D11DeviceContext::Wait(ID3D11Fence * pFence, UINT64 Value)
{
	return HRESULT __stdcall();
}
