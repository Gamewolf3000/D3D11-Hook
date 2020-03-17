#pragma once

#include "GlobalData.h"

typedef HRESULT(__stdcall *D3D11_DeviceContext_RSSetStateType)(ID3D11DeviceContext*, ID3D11RasterizerState *);
typedef HRESULT(__stdcall *D3D11_DeviceContext_VSSetShaderType)(ID3D11DeviceContext*, ID3D11VertexShader*, ID3D11ClassInstance*const*, UINT);
typedef HRESULT(__stdcall *D3D11_DeviceContext_DrawIndexedType)(ID3D11DeviceContext*, UINT, UINT, INT); // 12
typedef HRESULT(__stdcall *D3D11_DeviceContext_DrawType)(ID3D11DeviceContext*, UINT, UINT); // 13
typedef HRESULT(__stdcall *D3D11_DeviceContext_PSSetShaderType)(ID3D11DeviceContext*, ID3D11PixelShader*, ID3D11ClassInstance*const*, UINT); // 9
typedef HRESULT(__stdcall *D3D11_DeviceContext_DrawIndexedInstancedType)(ID3D11DeviceContext*, UINT, UINT, UINT, INT, UINT); // 20
typedef HRESULT(__stdcall *D3D11_DeviceContext_DrawInstancedType)(ID3D11DeviceContext*, UINT, UINT, UINT, UINT); // 21
typedef HRESULT(__stdcall *D3D11_DeviceContext_GSSetShaderType)(ID3D11DeviceContext*, ID3D11GeometryShader*, ID3D11ClassInstance*const*, UINT); // 23
typedef HRESULT(__stdcall *D3D11_DeviceContext_DrawIndexedInstancedIndirectType)(ID3D11DeviceContext*, ID3D11Buffer*, UINT); // 39
typedef HRESULT(__stdcall *D3D11_DeviceContext_DrawInstancedIndirectType)(ID3D11DeviceContext*, ID3D11Buffer*, UINT); // 40
typedef HRESULT(__stdcall *D3D11_DeviceContext_HSSetShaderType)(ID3D11DeviceContext*, ID3D11HullShader*, ID3D11ClassInstance*const*, UINT); // 60
typedef HRESULT(__stdcall *D3D11_DeviceContext_DSSetShaderType)(ID3D11DeviceContext*, ID3D11DomainShader*, ID3D11ClassInstance*const*, UINT); // 64



// From d3d11_3.h
// 9 = PSSetShader
// 20 = DrawIndexedInstanced
// 21 = DrawInstanced
// 23 = GSSetShader
// 39 = DrawIndexedInstancedIndirect
// 40 = DrawInstancedIndirect
// 60 = HSSetShader
// 64 = DSSetShader


class DeviceContextOverride
{
	static DeviceContextOverride* instance;

	ID3D11DeviceContext* deviceContext;
	ID3D11DeviceContext1* deviceContext1;
	ID3D11DeviceContext2* deviceContext2;
	ID3D11DeviceContext3* deviceContext3;
	ID3D11DeviceContext4* deviceContext4;

	D3DResolve* d3d_resolve_;

	HardHook hook_RSSetState;
	HardHook hook_VSSetShader;
	HardHook hook_DrawIndexed;
	HardHook hook_Draw;
	HardHook hook_PSSetShader;
	HardHook hook_DrawIndexedInstanced;
	HardHook hook_DrawInstanced;
	HardHook hook_GSSetShader;
	HardHook hook_DrawIndexedInstancedIndirect;
	HardHook hook_DrawInstancedIndirect;
	HardHook hook_HSSetShader;
	HardHook hook_DSSetShader;


	DeviceContextOverride()
	{
		deviceContext = nullptr;
		deviceContext1 = nullptr;
		deviceContext2 = nullptr;
		deviceContext3 = nullptr;
		deviceContext4 = nullptr;
	}

public:

	ID3D11DeviceContext* GetDeviceContext()
	{
		return deviceContext;
	}
	
	static DeviceContextOverride* GetInstance();

	HRESULT Init(ID3D11DeviceContext* deviceContext)
	{
		this->deviceContext = deviceContext;

		// Setup Hooks
		hook_RSSetState.SetupInterface(deviceContext, 43, reinterpret_cast<voidFunc>(RSSetState)); // d3d_4.h 43
		hook_VSSetShader.SetupInterface(deviceContext, 11, reinterpret_cast<voidFunc>(VSSetShader)); // 11
		hook_DrawIndexed.SetupInterface(deviceContext, 12, reinterpret_cast<voidFunc>(DrawIndexed));
		hook_Draw.SetupInterface(deviceContext, 13, reinterpret_cast<voidFunc>(Draw));

		hook_PSSetShader.SetupInterface(deviceContext, 9, reinterpret_cast<voidFunc>(PSSetShader));
		hook_DrawIndexedInstanced.SetupInterface(deviceContext, 20, reinterpret_cast<voidFunc>(DrawIndexedInstanced));
		hook_DrawInstanced.SetupInterface(deviceContext, 21, reinterpret_cast<voidFunc>(DrawInstanced));

		hook_DrawInstanced.SetupInterface(deviceContext, 23, reinterpret_cast<voidFunc>(GSSetShader));
		hook_DrawInstanced.SetupInterface(deviceContext, 39, reinterpret_cast<voidFunc>(DrawIndexedInstancedIndirect));
		hook_DrawInstanced.SetupInterface(deviceContext, 40, reinterpret_cast<voidFunc>(DrawInstancedIndirect));
		hook_DrawInstanced.SetupInterface(deviceContext, 60, reinterpret_cast<voidFunc>(HSSetShader));
		hook_DrawInstanced.SetupInterface(deviceContext, 64, reinterpret_cast<voidFunc>(DSSetShader));



		//MessageBoxA(0, "Done setting up devicecontext interface!", "", 0); 11

		return S_OK;
	}

	void CopySharedResource(ID3D11Resource* &original, ID3D11Resource* &copy)
	{
		ID3D11Texture2D* texture = (ID3D11Texture2D*)copy;
		D3D11_TEXTURE2D_DESC desc;

		texture->GetDesc(&desc);

		for (UINT item = 0; item < desc.ArraySize; ++item)
		{
			for (UINT level = 0; level < desc.MipLevels; ++level)
			{
				UINT index = D3D11CalcSubresource(level, item, desc.MipLevels);
				GlobalDeviceContext->ResolveSubresource(copy, index, original, index, desc.Format);
			}
		}

		//deviceContext->CopyResource(copy, original);
	}

	static void __stdcall RSSetState(ID3D11DeviceContext* devicecontext, ID3D11RasterizerState *pRasterizerState)
	{
		DeviceContextOverride::GetInstance()->RSSetStateInternal(devicecontext, pRasterizerState);
	}

	void RSSetStateInternal(ID3D11DeviceContext* devicecontext, ID3D11RasterizerState *pRasterizerState)
	{
		for (auto& stateData : rData)
		{
			if (stateData.original == pRasterizerState)
			{
				if (stateData.useWireframe)
					pRasterizerState = stateData.wireframe;

				break;
			}
		}

		D3D11_DeviceContext_RSSetStateType oRSSetState = (D3D11_DeviceContext_RSSetStateType)hook_RSSetState.call;
		hook_RSSetState.Restore();
		oRSSetState(devicecontext, pRasterizerState);
		hook_RSSetState.Inject();
		perFrameStats.nrOfRasterizerStates.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall VSSetShader(ID3D11DeviceContext* devicecontext, ID3D11VertexShader* pVertexShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		DeviceContextOverride::GetInstance()->VSSetShaderInternal(devicecontext, pVertexShader, ppClassInstances, NumClassInstances);
	}

	void VSSetShaderInternal(ID3D11DeviceContext* devicecontext, ID3D11VertexShader* pVertexShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		//MessageBoxA(0, "My set vs shader function was called!", "", 0);
		D3D11_DeviceContext_VSSetShaderType oVSSetShader = (D3D11_DeviceContext_VSSetShaderType)hook_VSSetShader.call;
		hook_VSSetShader.Restore();
		oVSSetShader(devicecontext, pVertexShader, ppClassInstances, NumClassInstances);
		hook_VSSetShader.Inject();
		perFrameStats.nrOfVertexShadersUsed.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall DrawIndexed(ID3D11DeviceContext* devicecontext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		DeviceContextOverride::GetInstance()->DrawIndexedInternal(devicecontext, IndexCount, StartIndexLocation, BaseVertexLocation);
	}

	void DrawIndexedInternal(ID3D11DeviceContext* devicecontext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		D3D11_DeviceContext_DrawIndexedType oDrawIndexed = (D3D11_DeviceContext_DrawIndexedType)hook_DrawIndexed.call;
		hook_DrawIndexed.Restore();
		oDrawIndexed(devicecontext, IndexCount, StartIndexLocation, BaseVertexLocation);
		hook_DrawIndexed.Inject();
		perFrameStats.nrOfDrawIndexedCalls.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall Draw(ID3D11DeviceContext* devicecontext, UINT VertexCount, UINT StartVertexLocation)
	{
		DeviceContextOverride::GetInstance()->DrawInternal(devicecontext, VertexCount, StartVertexLocation);
	}

	void DrawInternal(ID3D11DeviceContext* devicecontext, UINT VertexCount, UINT StartVertexLocation)
	{
		D3D11_DeviceContext_DrawType oDraw = (D3D11_DeviceContext_DrawType)hook_Draw.call;
		hook_Draw.Restore();
		oDraw(devicecontext, VertexCount, StartVertexLocation);
		hook_Draw.Inject();
		perFrameStats.nrOfDrawCalls.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall PSSetShader(ID3D11DeviceContext* devicecontext, ID3D11PixelShader* pPixelShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		DeviceContextOverride::GetInstance()->PSSetShaderInternal(devicecontext, pPixelShader, ppClassInstances, NumClassInstances);
	}

	void PSSetShaderInternal(ID3D11DeviceContext* devicecontext, ID3D11PixelShader* pPixelShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		//MessageBoxA(0, "My set ps shader function was called!", "", 0);
		D3D11_DeviceContext_PSSetShaderType oPSSetShader = (D3D11_DeviceContext_PSSetShaderType)hook_PSSetShader.call;
		hook_PSSetShader.Restore();
		oPSSetShader(devicecontext, pPixelShader, ppClassInstances, NumClassInstances);
		hook_PSSetShader.Inject();
		perFrameStats.nrOfPixelShadersUsed.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall DrawIndexedInstanced(ID3D11DeviceContext* devicecontext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
	{
		DeviceContextOverride::GetInstance()->DrawIndexedInstancedInternal(devicecontext, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
	}

	void DrawIndexedInstancedInternal(ID3D11DeviceContext* devicecontext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
	{
		D3D11_DeviceContext_DrawIndexedInstancedType oDrawIndexedInstanced = (D3D11_DeviceContext_DrawIndexedInstancedType)hook_DrawIndexedInstanced.call;
		hook_DrawIndexedInstanced.Restore();
		oDrawIndexedInstanced(devicecontext, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
		hook_DrawIndexedInstanced.Inject();
		perFrameStats.nrOfDrawIndexedInstancedCalls.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall DrawInstanced(ID3D11DeviceContext* devicecontext, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
	{
		DeviceContextOverride::GetInstance()->DrawInstancedInternal(devicecontext, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
	}

	void DrawInstancedInternal(ID3D11DeviceContext* devicecontext, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
	{
		D3D11_DeviceContext_DrawInstancedType oDrawInstanced = (D3D11_DeviceContext_DrawInstancedType)hook_DrawInstanced.call;
		hook_DrawInstanced.Restore();
		oDrawInstanced(devicecontext, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
		hook_DrawInstanced.Inject();
		perFrameStats.nrOfDrawInstancedCalls.fetch_add(1, std::memory_order_relaxed);
	}



	
	static void __stdcall GSSetShader(ID3D11DeviceContext* devicecontext, ID3D11GeometryShader * pGeometryShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		DeviceContextOverride::GetInstance()->GSSetShaderInternal(devicecontext, pGeometryShader, ppClassInstances, NumClassInstances);
	}

	void GSSetShaderInternal(ID3D11DeviceContext* devicecontext, ID3D11GeometryShader * pGeometryShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		//MessageBoxA(0, "My set gs shader function was called!", "", 0);
		D3D11_DeviceContext_GSSetShaderType oGSSetShader = (D3D11_DeviceContext_GSSetShaderType)hook_GSSetShader.call;
		hook_GSSetShader.Restore();
		oGSSetShader(devicecontext, pGeometryShader, ppClassInstances, NumClassInstances);
		hook_GSSetShader.Inject();
		perFrameStats.nrOfGeometryShadersUsed.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall DrawIndexedInstancedIndirect(ID3D11DeviceContext* devicecontext, ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs)
	{
		DeviceContextOverride::GetInstance()->DrawIndexedInstancedIndirectInternal(devicecontext, pBufferForArgs, AlignedByteOffsetForArgs);
	}

	void DrawIndexedInstancedIndirectInternal(ID3D11DeviceContext* devicecontext, ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs)
	{
		D3D11_DeviceContext_DrawIndexedInstancedIndirectType oDrawIndexedInstancedIndirect = (D3D11_DeviceContext_DrawIndexedInstancedIndirectType)hook_DrawIndexedInstancedIndirect.call;
		hook_DrawIndexedInstancedIndirect.Restore();
		oDrawIndexedInstancedIndirect(devicecontext, pBufferForArgs, AlignedByteOffsetForArgs);
		hook_DrawIndexedInstancedIndirect.Inject();
		perFrameStats.nrOfDrawIndexedInstancedIndirectCalls.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall DrawInstancedIndirect(ID3D11DeviceContext* devicecontext, ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs)
	{
		DeviceContextOverride::GetInstance()->DrawInstancedIndirectInternal(devicecontext, pBufferForArgs, AlignedByteOffsetForArgs);
	}

	void DrawInstancedIndirectInternal(ID3D11DeviceContext* devicecontext, ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs)
	{
		D3D11_DeviceContext_DrawInstancedIndirectType oDrawInstancedIndirect = (D3D11_DeviceContext_DrawInstancedIndirectType)hook_DrawInstancedIndirect.call;
		hook_DrawInstancedIndirect.Restore();
		oDrawInstancedIndirect(devicecontext, pBufferForArgs, AlignedByteOffsetForArgs);
		hook_DrawInstancedIndirect.Inject();
		perFrameStats.nrOfDrawInstancedIndirectCalls.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall HSSetShader(ID3D11DeviceContext* devicecontext, ID3D11HullShader * pHullShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		DeviceContextOverride::GetInstance()->HSSetShaderInternal(devicecontext, pHullShader, ppClassInstances, NumClassInstances);
	}

	void HSSetShaderInternal(ID3D11DeviceContext* devicecontext, ID3D11HullShader * pHullShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		//MessageBoxA(0, "My set hs shader function was called!", "", 0);
		D3D11_DeviceContext_HSSetShaderType oHSSetShader = (D3D11_DeviceContext_HSSetShaderType)hook_HSSetShader.call;
		hook_HSSetShader.Restore();
		oHSSetShader(devicecontext, pHullShader, ppClassInstances, NumClassInstances);
		hook_HSSetShader.Inject();
		perFrameStats.nrOfHullShadersUsed.fetch_add(1, std::memory_order_relaxed);
	}

	static void __stdcall DSSetShader(ID3D11DeviceContext* devicecontext, ID3D11DomainShader * pDomainShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		DeviceContextOverride::GetInstance()->DSSetShaderInternal(devicecontext, pDomainShader, ppClassInstances, NumClassInstances);
	}

	void DSSetShaderInternal(ID3D11DeviceContext* devicecontext, ID3D11DomainShader * pDomainShader, ID3D11ClassInstance*const* ppClassInstances, UINT NumClassInstances)
	{
		//MessageBoxA(0, "My set hs shader function was called!", "", 0);
		D3D11_DeviceContext_DSSetShaderType oDSSetShader = (D3D11_DeviceContext_DSSetShaderType)hook_DSSetShader.call;
		hook_DSSetShader.Restore();
		oDSSetShader(devicecontext, pDomainShader, ppClassInstances, NumClassInstances);
		hook_DSSetShader.Inject();
		perFrameStats.nrOfDomainShadersUsed.fetch_add(1, std::memory_order_relaxed);
	}
};

DeviceContextOverride* DeviceContextOverride::instance = nullptr;
DeviceContextOverride* DeviceContextOverride::GetInstance()
{
	if (!instance)
		instance = new DeviceContextOverride();

	return instance;
}