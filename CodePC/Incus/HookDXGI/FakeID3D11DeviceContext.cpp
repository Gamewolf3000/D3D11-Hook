#include "FakeID3D11DeviceContext.h"
#include "FakeID3D11Device.hpp"

FakeID3D11DeviceContext::FakeID3D11DeviceContext(ID3D11DeviceContext * real, FakeID3D11Device* creator)
{
	realDeviceContext = static_cast<ID3D11DeviceContext4*>(real);
	creatorDevice = creator;
}

HRESULT __stdcall FakeID3D11DeviceContext::QueryInterface(REFIID riid, void ** ppvObject)
{
	return realDeviceContext->QueryInterface(riid, ppvObject);
}

ULONG __stdcall FakeID3D11DeviceContext::AddRef(void)
{
	return realDeviceContext->AddRef();
}

ULONG __stdcall FakeID3D11DeviceContext::Release(void)
{
	return realDeviceContext->Release();
}

void __stdcall FakeID3D11DeviceContext::GetDevice(ID3D11Device ** ppDevice)
{
	creatorDevice->AddRef();
	*ppDevice = creatorDevice;
}

HRESULT __stdcall FakeID3D11DeviceContext::GetPrivateData(REFGUID guid, UINT * pDataSize, void * pData)
{
	return realDeviceContext->GetPrivateData(guid, pDataSize, pData);
}

HRESULT __stdcall FakeID3D11DeviceContext::SetPrivateData(REFGUID guid, UINT DataSize, const void * pData)
{
	return realDeviceContext->SetPrivateData(guid, DataSize, pData);
}

HRESULT __stdcall FakeID3D11DeviceContext::SetPrivateDataInterface(REFGUID guid, const IUnknown * pData)
{
	return realDeviceContext->SetPrivateDataInterface(guid, pData);
}

void __stdcall FakeID3D11DeviceContext::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	realDeviceContext->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	realDeviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::PSSetShader(ID3D11PixelShader * pPixelShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	realDeviceContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	realDeviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::VSSetShader(ID3D11VertexShader * pVertexShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	realDeviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	realDeviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void __stdcall FakeID3D11DeviceContext::Draw(UINT VertexCount, UINT StartVertexLocation)
{
	realDeviceContext->Draw(VertexCount, StartVertexLocation);
}

HRESULT __stdcall FakeID3D11DeviceContext::Map(ID3D11Resource * pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE * pMappedResource)
{
	return realDeviceContext->Map(pResource, Subresource, MapType, MapFlags, pMappedResource);
}

void __stdcall FakeID3D11DeviceContext::Unmap(ID3D11Resource * pResource, UINT Subresource)
{
	realDeviceContext->Unmap(pResource, Subresource);
}

void __stdcall FakeID3D11DeviceContext::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	realDeviceContext->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::IASetInputLayout(ID3D11InputLayout * pInputLayout)
{
	realDeviceContext->IASetInputLayout(pInputLayout);
}

void __stdcall FakeID3D11DeviceContext::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppVertexBuffers, const UINT * pStrides, const UINT * pOffsets)
{
	realDeviceContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void __stdcall FakeID3D11DeviceContext::IASetIndexBuffer(ID3D11Buffer * pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
{
	realDeviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void __stdcall FakeID3D11DeviceContext::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
	realDeviceContext->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

void __stdcall FakeID3D11DeviceContext::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
	realDeviceContext->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

void __stdcall FakeID3D11DeviceContext::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	realDeviceContext->GSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::GSSetShader(ID3D11GeometryShader * pShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	realDeviceContext->GSSetShader(pShader, ppClassInstances, NumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	realDeviceContext->IASetPrimitiveTopology(Topology);
}

void __stdcall FakeID3D11DeviceContext::VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	realDeviceContext->VSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	realDeviceContext->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::Begin(ID3D11Asynchronous * pAsync)
{
	realDeviceContext->Begin(pAsync);
}

void __stdcall FakeID3D11DeviceContext::End(ID3D11Asynchronous * pAsync)
{
	realDeviceContext->End(pAsync);
}

HRESULT __stdcall FakeID3D11DeviceContext::GetData(ID3D11Asynchronous * pAsync, void * pData, UINT DataSize, UINT GetDataFlags)
{
	return realDeviceContext->GetData(pAsync, pData, DataSize, GetDataFlags);
}

void __stdcall FakeID3D11DeviceContext::SetPredication(ID3D11Predicate * pPredicate, BOOL PredicateValue)
{
	realDeviceContext->SetPredication(pPredicate, PredicateValue);
}

void __stdcall FakeID3D11DeviceContext::GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	realDeviceContext->GSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	realDeviceContext->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView * const * ppRenderTargetViews, ID3D11DepthStencilView * pDepthStencilView)
{
	realDeviceContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

void __stdcall FakeID3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView * const * ppRenderTargetViews, ID3D11DepthStencilView * pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView * const * ppUnorderedAccessViews, const UINT * pUAVInitialCounts)
{
	realDeviceContext->OMSetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, pDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}

void __stdcall FakeID3D11DeviceContext::OMSetBlendState(ID3D11BlendState * pBlendState, const FLOAT BlendFactor[4], UINT SampleMask)
{
	realDeviceContext->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
}

void __stdcall FakeID3D11DeviceContext::OMSetDepthStencilState(ID3D11DepthStencilState * pDepthStencilState, UINT StencilRef)
{
	realDeviceContext->OMSetDepthStencilState(pDepthStencilState, StencilRef);
}

void __stdcall FakeID3D11DeviceContext::SOSetTargets(UINT NumBuffers, ID3D11Buffer * const * ppSOTargets, const UINT * pOffsets)
{
	realDeviceContext->SOSetTargets(NumBuffers, ppSOTargets, pOffsets);
}

void __stdcall FakeID3D11DeviceContext::DrawAuto(void)
{
	realDeviceContext->DrawAuto();
}

void __stdcall FakeID3D11DeviceContext::DrawIndexedInstancedIndirect(ID3D11Buffer * pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	realDeviceContext->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void __stdcall FakeID3D11DeviceContext::DrawInstancedIndirect(ID3D11Buffer * pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	realDeviceContext->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void __stdcall FakeID3D11DeviceContext::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
	realDeviceContext->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

void __stdcall FakeID3D11DeviceContext::DispatchIndirect(ID3D11Buffer * pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	realDeviceContext->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void __stdcall FakeID3D11DeviceContext::RSSetState(ID3D11RasterizerState * pRasterizerState)
{
	realDeviceContext->RSSetState(pRasterizerState);
}

void __stdcall FakeID3D11DeviceContext::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT * pViewports)
{
	realDeviceContext->RSSetViewports(NumViewports, pViewports);
}

void __stdcall FakeID3D11DeviceContext::RSSetScissorRects(UINT NumRects, const D3D11_RECT * pRects)
{
	realDeviceContext->RSSetScissorRects(NumRects, pRects);
}

void __stdcall FakeID3D11DeviceContext::CopySubresourceRegion(ID3D11Resource * pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource * pSrcResource, UINT SrcSubresource, const D3D11_BOX * pSrcBox)
{
	realDeviceContext->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
}

void __stdcall FakeID3D11DeviceContext::CopyResource(ID3D11Resource * pDstResource, ID3D11Resource * pSrcResource)
{
	realDeviceContext->CopyResource(pDstResource, pSrcResource);
}

void __stdcall FakeID3D11DeviceContext::UpdateSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	realDeviceContext->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void __stdcall FakeID3D11DeviceContext::CopyStructureCount(ID3D11Buffer * pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView * pSrcView)
{
	realDeviceContext->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
}

void __stdcall FakeID3D11DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView * pRenderTargetView, const FLOAT ColorRGBA[4])
{
	realDeviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void __stdcall FakeID3D11DeviceContext::ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView * pUnorderedAccessView, const UINT Values[4])
{
	realDeviceContext->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
}

void __stdcall FakeID3D11DeviceContext::ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView * pUnorderedAccessView, const FLOAT Values[4])
{
	realDeviceContext->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
}

void __stdcall FakeID3D11DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView * pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil)
{
	realDeviceContext->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void __stdcall FakeID3D11DeviceContext::GenerateMips(ID3D11ShaderResourceView * pShaderResourceView)
{
	realDeviceContext->GenerateMips(pShaderResourceView);
}

void __stdcall FakeID3D11DeviceContext::SetResourceMinLOD(ID3D11Resource * pResource, FLOAT MinLOD)
{
	realDeviceContext->SetResourceMinLOD(pResource, MinLOD);
}

FLOAT __stdcall FakeID3D11DeviceContext::GetResourceMinLOD(ID3D11Resource * pResource)
{
	return realDeviceContext->GetResourceMinLOD(pResource);
}

void __stdcall FakeID3D11DeviceContext::ResolveSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, ID3D11Resource * pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format)
{
	realDeviceContext->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}

void __stdcall FakeID3D11DeviceContext::ExecuteCommandList(ID3D11CommandList * pCommandList, BOOL RestoreContextState)
{
	realDeviceContext->ExecuteCommandList(pCommandList, RestoreContextState);
}

void __stdcall FakeID3D11DeviceContext::HSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	realDeviceContext->HSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::HSSetShader(ID3D11HullShader * pHullShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	realDeviceContext->HSSetShader(pHullShader, ppClassInstances, NumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	realDeviceContext->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	realDeviceContext->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	realDeviceContext->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::DSSetShader(ID3D11DomainShader * pDomainShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	realDeviceContext->DSSetShader(pDomainShader, ppClassInstances, NumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	realDeviceContext->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	realDeviceContext->DSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::CSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView * const * ppShaderResourceViews)
{
	realDeviceContext->CSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView * const * ppUnorderedAccessViews, const UINT * pUAVInitialCounts)
{
	realDeviceContext->CSSetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}

void __stdcall FakeID3D11DeviceContext::CSSetShader(ID3D11ComputeShader * pComputeShader, ID3D11ClassInstance * const * ppClassInstances, UINT NumClassInstances)
{
	realDeviceContext->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState * const * ppSamplers)
{
	realDeviceContext->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers)
{
	realDeviceContext->CSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	realDeviceContext->VSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	realDeviceContext->PSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::PSGetShader(ID3D11PixelShader ** ppPixelShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	realDeviceContext->PSGetShader(ppPixelShader, ppClassInstances, pNumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	realDeviceContext->PSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::VSGetShader(ID3D11VertexShader ** ppVertexShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	realDeviceContext->VSGetShader(ppVertexShader, ppClassInstances, pNumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	realDeviceContext->PSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::IAGetInputLayout(ID3D11InputLayout ** ppInputLayout)
{
	realDeviceContext->IAGetInputLayout(ppInputLayout);
}

void __stdcall FakeID3D11DeviceContext::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppVertexBuffers, UINT * pStrides, UINT * pOffsets)
{
	realDeviceContext->IAGetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void __stdcall FakeID3D11DeviceContext::IAGetIndexBuffer(ID3D11Buffer ** pIndexBuffer, DXGI_FORMAT * Format, UINT * Offset)
{
	realDeviceContext->IAGetIndexBuffer(pIndexBuffer, Format, Offset);
}

void __stdcall FakeID3D11DeviceContext::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	realDeviceContext->GSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::GSGetShader(ID3D11GeometryShader ** ppGeometryShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	realDeviceContext->GSGetShader(ppGeometryShader, ppClassInstances, pNumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY * pTopology)
{
	realDeviceContext->IAGetPrimitiveTopology(pTopology);
}

void __stdcall FakeID3D11DeviceContext::VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	realDeviceContext->VSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	realDeviceContext->VSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::GetPredication(ID3D11Predicate ** ppPredicate, BOOL * pPredicateValue)
{
	realDeviceContext->GetPredication(ppPredicate, pPredicateValue);
}

void __stdcall FakeID3D11DeviceContext::GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	realDeviceContext->GSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	realDeviceContext->GSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView ** ppRenderTargetViews, ID3D11DepthStencilView ** ppDepthStencilView)
{
	realDeviceContext->OMGetRenderTargets(NumViews, ppRenderTargetViews, ppDepthStencilView);
}

void __stdcall FakeID3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView ** ppRenderTargetViews, ID3D11DepthStencilView ** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView ** ppUnorderedAccessViews)
{
	realDeviceContext->OMGetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, ppDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
}

void __stdcall FakeID3D11DeviceContext::OMGetBlendState(ID3D11BlendState ** ppBlendState, FLOAT BlendFactor[4], UINT * pSampleMask)
{
	realDeviceContext->OMGetBlendState(ppBlendState, BlendFactor, pSampleMask);
}

void __stdcall FakeID3D11DeviceContext::OMGetDepthStencilState(ID3D11DepthStencilState ** ppDepthStencilState, UINT * pStencilRef)
{
	realDeviceContext->OMGetDepthStencilState(ppDepthStencilState, pStencilRef);
}

void __stdcall FakeID3D11DeviceContext::SOGetTargets(UINT NumBuffers, ID3D11Buffer ** ppSOTargets)
{
	realDeviceContext->SOGetTargets(NumBuffers, ppSOTargets);
}

void __stdcall FakeID3D11DeviceContext::RSGetState(ID3D11RasterizerState ** ppRasterizerState)
{
	realDeviceContext->RSGetState(ppRasterizerState);
}

void __stdcall FakeID3D11DeviceContext::RSGetViewports(UINT * pNumViewports, D3D11_VIEWPORT * pViewports)
{
	realDeviceContext->RSGetViewports(pNumViewports, pViewports);
}

void __stdcall FakeID3D11DeviceContext::RSGetScissorRects(UINT * pNumRects, D3D11_RECT * pRects)
{
	realDeviceContext->RSGetScissorRects(pNumRects, pRects);
}

void __stdcall FakeID3D11DeviceContext::HSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	realDeviceContext->HSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::HSGetShader(ID3D11HullShader ** ppHullShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	realDeviceContext->HSGetShader(ppHullShader, ppClassInstances, pNumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	realDeviceContext->HSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	realDeviceContext->HSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::DSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	realDeviceContext->DSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::DSGetShader(ID3D11DomainShader ** ppDomainShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	realDeviceContext->DSGetShader(ppDomainShader, ppClassInstances, pNumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	realDeviceContext->DSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	realDeviceContext->DSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::CSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView ** ppShaderResourceViews)
{
	realDeviceContext->CSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall FakeID3D11DeviceContext::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView ** ppUnorderedAccessViews)
{
	realDeviceContext->CSGetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews);
}

void __stdcall FakeID3D11DeviceContext::CSGetShader(ID3D11ComputeShader ** ppComputeShader, ID3D11ClassInstance ** ppClassInstances, UINT * pNumClassInstances)
{
	realDeviceContext->CSGetShader(ppComputeShader, ppClassInstances, pNumClassInstances);
}

void __stdcall FakeID3D11DeviceContext::CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState ** ppSamplers)
{
	realDeviceContext->CSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void __stdcall FakeID3D11DeviceContext::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers)
{
	realDeviceContext->CSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void __stdcall FakeID3D11DeviceContext::ClearState(void)
{
	realDeviceContext->ClearState();
}

void __stdcall FakeID3D11DeviceContext::Flush(void)
{
	realDeviceContext->Flush();
}

D3D11_DEVICE_CONTEXT_TYPE __stdcall FakeID3D11DeviceContext::GetType(void)
{
	return realDeviceContext->GetType();
}

UINT __stdcall FakeID3D11DeviceContext::GetContextFlags(void)
{
	return realDeviceContext->GetContextFlags();
}

HRESULT __stdcall FakeID3D11DeviceContext::FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList ** ppCommandList)
{
	return realDeviceContext->FinishCommandList(RestoreDeferredContextState, ppCommandList);
}

void __stdcall FakeID3D11DeviceContext::CopySubresourceRegion1(ID3D11Resource * pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource * pSrcResource, UINT SrcSubresource, const D3D11_BOX * pSrcBox, UINT CopyFlags)
{
	realDeviceContext->CopySubresourceRegion1(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox, CopyFlags);
}

void __stdcall FakeID3D11DeviceContext::UpdateSubresource1(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch, UINT CopyFlags)
{
	realDeviceContext->UpdateSubresource1(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch, CopyFlags);
}

void __stdcall FakeID3D11DeviceContext::DiscardResource(ID3D11Resource * pResource)
{
	realDeviceContext->DiscardResource(pResource);
}

void __stdcall FakeID3D11DeviceContext::DiscardView(ID3D11View * pResourceView)
{
	realDeviceContext->DiscardView(pResourceView);
}

void __stdcall FakeID3D11DeviceContext::VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	realDeviceContext->VSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	realDeviceContext->HSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	realDeviceContext->DSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	realDeviceContext->GSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	realDeviceContext->PSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer * const * ppConstantBuffers, const UINT * pFirstConstant, const UINT * pNumConstants)
{
	realDeviceContext->CSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	realDeviceContext->VSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	realDeviceContext->HSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	realDeviceContext->DSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	realDeviceContext->GSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	realDeviceContext->PSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer ** ppConstantBuffers, UINT * pFirstConstant, UINT * pNumConstants)
{
	realDeviceContext->CSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void __stdcall FakeID3D11DeviceContext::SwapDeviceContextState(ID3DDeviceContextState * pState, ID3DDeviceContextState ** ppPreviousState)
{
	realDeviceContext->SwapDeviceContextState(pState, ppPreviousState);
}

void __stdcall FakeID3D11DeviceContext::ClearView(ID3D11View * pView, const FLOAT Color[4], const D3D11_RECT * pRect, UINT NumRects)
{
	realDeviceContext->ClearView(pView, Color, pRect, NumRects);
}

void __stdcall FakeID3D11DeviceContext::DiscardView1(ID3D11View * pResourceView, const D3D11_RECT * pRects, UINT NumRects)
{
	realDeviceContext->DiscardView1(pResourceView, pRects, NumRects);
}

HRESULT __stdcall FakeID3D11DeviceContext::UpdateTileMappings(ID3D11Resource * pTiledResource, UINT NumTiledResourceRegions, const D3D11_TILED_RESOURCE_COORDINATE * pTiledResourceRegionStartCoordinates, const D3D11_TILE_REGION_SIZE * pTiledResourceRegionSizes, ID3D11Buffer * pTilePool, UINT NumRanges, const UINT * pRangeFlags, const UINT * pTilePoolStartOffsets, const UINT * pRangeTileCounts, UINT Flags)
{
	return realDeviceContext->UpdateTileMappings(pTiledResource, NumTiledResourceRegions, pTiledResourceRegionStartCoordinates, pTiledResourceRegionSizes, pTilePool, NumRanges, pRangeFlags, pTilePoolStartOffsets, pRangeTileCounts, Flags);
}

HRESULT __stdcall FakeID3D11DeviceContext::CopyTileMappings(ID3D11Resource * pDestTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pDestRegionStartCoordinate, ID3D11Resource * pSourceTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pSourceRegionStartCoordinate, const D3D11_TILE_REGION_SIZE * pTileRegionSize, UINT Flags)
{
	return realDeviceContext->CopyTileMappings(pDestTiledResource, pDestRegionStartCoordinate, pSourceTiledResource, pSourceRegionStartCoordinate, pTileRegionSize, Flags);
}

void __stdcall FakeID3D11DeviceContext::CopyTiles(ID3D11Resource * pTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE * pTileRegionSize, ID3D11Buffer * pBuffer, UINT64 BufferStartOffsetInBytes, UINT Flags)
{
	realDeviceContext->CopyTiles(pTiledResource, pTileRegionStartCoordinate, pTileRegionSize, pBuffer, BufferStartOffsetInBytes, Flags);
}

void __stdcall FakeID3D11DeviceContext::UpdateTiles(ID3D11Resource * pDestTiledResource, const D3D11_TILED_RESOURCE_COORDINATE * pDestTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE * pDestTileRegionSize, const void * pSourceTileData, UINT Flags)
{
	realDeviceContext->UpdateTiles(pDestTiledResource, pDestTileRegionStartCoordinate, pDestTileRegionSize, pSourceTileData, Flags);
}

HRESULT __stdcall FakeID3D11DeviceContext::ResizeTilePool(ID3D11Buffer * pTilePool, UINT64 NewSizeInBytes)
{
	return realDeviceContext->ResizeTilePool(pTilePool, NewSizeInBytes);
}

void __stdcall FakeID3D11DeviceContext::TiledResourceBarrier(ID3D11DeviceChild * pTiledResourceOrViewAccessBeforeBarrier, ID3D11DeviceChild * pTiledResourceOrViewAccessAfterBarrier)
{
	realDeviceContext->TiledResourceBarrier(pTiledResourceOrViewAccessBeforeBarrier, pTiledResourceOrViewAccessAfterBarrier);
}

BOOL __stdcall FakeID3D11DeviceContext::IsAnnotationEnabled(void)
{
	return realDeviceContext->IsAnnotationEnabled();
}

void __stdcall FakeID3D11DeviceContext::SetMarkerInt(LPCWSTR pLabel, INT Data)
{
	realDeviceContext->SetMarkerInt(pLabel, Data);
}

void __stdcall FakeID3D11DeviceContext::BeginEventInt(LPCWSTR pLabel, INT Data)
{
	realDeviceContext->BeginEventInt(pLabel, Data);
}

void __stdcall FakeID3D11DeviceContext::EndEvent(void)
{
	realDeviceContext->EndEvent();
}

void __stdcall FakeID3D11DeviceContext::Flush1(D3D11_CONTEXT_TYPE ContextType, HANDLE hEvent)
{
	realDeviceContext->Flush1(ContextType, hEvent);
}

void __stdcall FakeID3D11DeviceContext::SetHardwareProtectionState(BOOL HwProtectionEnable)
{
	realDeviceContext->SetHardwareProtectionState(HwProtectionEnable);
}

void __stdcall FakeID3D11DeviceContext::GetHardwareProtectionState(BOOL * pHwProtectionEnable)
{
	realDeviceContext->GetHardwareProtectionState(pHwProtectionEnable);
}

HRESULT __stdcall FakeID3D11DeviceContext::Signal(ID3D11Fence * pFence, UINT64 Value)
{
	return realDeviceContext->Signal(pFence, Value);
}

HRESULT __stdcall FakeID3D11DeviceContext::Wait(ID3D11Fence * pFence, UINT64 Value)
{
	return realDeviceContext->Wait(pFence, Value);
}
