#pragma once

#include "GlobalData.h"

typedef HRESULT(__stdcall *D3D11_Device_CreateBufferType)(ID3D11Device*, const D3D11_BUFFER_DESC*, const D3D11_SUBRESOURCE_DATA*, ID3D11Buffer**);
typedef HRESULT(__stdcall *D3D11_Device_CreateTexture2D)(ID3D11Device*, const D3D11_TEXTURE2D_DESC*, const D3D11_SUBRESOURCE_DATA*, ID3D11Texture2D**);
typedef HRESULT(__stdcall *D3D11_Device_CreateRenderTargetView)(ID3D11Device* , ID3D11Resource*, const D3D11_RENDER_TARGET_VIEW_DESC *, ID3D11RenderTargetView**);
typedef HRESULT(__stdcall *D3D11_Device_CreateDepthStencilView)(ID3D11Device*, ID3D11Resource*, const D3D11_DEPTH_STENCIL_VIEW_DESC*, ID3D11DepthStencilView**);
typedef HRESULT(__stdcall *D3D11_Device_CreateInputLayout)(ID3D11Device*, const D3D11_INPUT_ELEMENT_DESC *, UINT, const void*, SIZE_T, ID3D11InputLayout**);
typedef HRESULT(__stdcall *D3D11_Device_CreateVertexShaderType)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11VertexShader**);
typedef HRESULT(__stdcall *D3D11_Device_CreateGeometryShaderType)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11GeometryShader**);
typedef HRESULT(__stdcall *D3D11_Device_CreateGeometryShaderWithStreamOutputType)(ID3D11Device*, const void*, SIZE_T, const D3D11_SO_DECLARATION_ENTRY*, UINT, const UINT*, UINT, UINT, ID3D11ClassLinkage*, ID3D11GeometryShader**);
typedef HRESULT(__stdcall *D3D11_Device_CreatePixelShaderType)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11PixelShader**);
typedef HRESULT(__stdcall *D3D11_Device_CreateHullShaderType)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11HullShader**);
typedef HRESULT(__stdcall *D3D11_Device_CreateDomainShaderType)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11DomainShader**);
typedef HRESULT(__stdcall *D3D11_Device_CreateComputeShaderType)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11ComputeShader**);
typedef HRESULT(__stdcall *D3D11_Device_CreateRasterizerStateType)(ID3D11Device*, const D3D11_RASTERIZER_DESC*, ID3D11RasterizerState**);

class DeviceOverride
{
	static DeviceOverride* instance;

	ID3D11Device* device;
	ID3D11Device1* device1;
	ID3D11Device2* device2;
	ID3D11Device3* device3;
	ID3D11Device4* device4;
	ID3D11Device5* device5;
	D3DResolve* d3d_resolve_;

	DeviceOverride()
	{
		device = nullptr;
		device1 = nullptr;
		device2 = nullptr;
		device3 = nullptr;
		device4 = nullptr;
		device5 = nullptr;
	}

	HardHook hook_CreateBuffer;
	HardHook hook_CreateTexture2D;
	HardHook hook_CreateRenderTargetView;
	HardHook hook_CreateDepthStencilView;
	HardHook hook_CreateInputLayout;
	HardHook hook_CreateVertexShader;
	HardHook hook_CreateGeometryShader;
	HardHook hook_CreateGeometryShaderWithStreamOutput;
	HardHook hook_CreatePixelShader;
	HardHook hook_CreateDomainShader;
	HardHook hook_CreateHullShader;
	HardHook hook_CreateComputeShader;
	HardHook hook_CreateRasterizerState;

	DXGI_FORMAT EnsureNotTypeless(DXGI_FORMAT fmt)
	{
		// Assumes UNORM or FLOAT; doesn't use UINT or SINT
		switch (fmt)
		{
		case DXGI_FORMAT_R32G32B32A32_TYPELESS: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case DXGI_FORMAT_R32G32B32_TYPELESS:    return DXGI_FORMAT_R32G32B32_FLOAT;
		case DXGI_FORMAT_R16G16B16A16_TYPELESS: return DXGI_FORMAT_R16G16B16A16_UNORM;
		case DXGI_FORMAT_R32G32_TYPELESS:       return DXGI_FORMAT_R32G32_FLOAT;
		case DXGI_FORMAT_R10G10B10A2_TYPELESS:  return DXGI_FORMAT_R10G10B10A2_UNORM;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:     return DXGI_FORMAT_R8G8B8A8_UNORM;
		case DXGI_FORMAT_R16G16_TYPELESS:       return DXGI_FORMAT_R16G16_UNORM;
		case DXGI_FORMAT_R32_TYPELESS:          return DXGI_FORMAT_R32_FLOAT;
		case DXGI_FORMAT_R8G8_TYPELESS:         return DXGI_FORMAT_R8G8_UNORM;
		case DXGI_FORMAT_R16_TYPELESS:          return DXGI_FORMAT_R16_UNORM;
		case DXGI_FORMAT_R8_TYPELESS:           return DXGI_FORMAT_R8_UNORM;
		case DXGI_FORMAT_BC1_TYPELESS:          return DXGI_FORMAT_BC1_UNORM;
		case DXGI_FORMAT_BC2_TYPELESS:          return DXGI_FORMAT_BC2_UNORM;
		case DXGI_FORMAT_BC3_TYPELESS:          return DXGI_FORMAT_BC3_UNORM;
		case DXGI_FORMAT_BC4_TYPELESS:          return DXGI_FORMAT_BC4_UNORM;
		case DXGI_FORMAT_BC5_TYPELESS:          return DXGI_FORMAT_BC5_UNORM;
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:     return DXGI_FORMAT_B8G8R8A8_UNORM;
		case DXGI_FORMAT_B8G8R8X8_TYPELESS:     return DXGI_FORMAT_B8G8R8X8_UNORM;
		case DXGI_FORMAT_BC7_TYPELESS:          return DXGI_FORMAT_BC7_UNORM;
		default:                                return fmt;
		}
	}

	void HandleMultisampledResource(D3D11_TEXTURE2D_DESC& desc, ID3D11Texture2D* &copy)
	{
		HRESULT hr;
		// MSAA content must be resolved before being copied to a staging texture
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		hr = CreateTexture2DInternal(GlobalDevice, &desc, nullptr, &(copy));
		if (FAILED(hr))
			throw("Failed to create copy texture when handling multisampled resource");

		DXGI_FORMAT fmt = EnsureNotTypeless(desc.Format);

		UINT support = 0;
		hr = GlobalDevice->CheckFormatSupport(fmt, &support);
		if (FAILED(hr))
			throw("Error checking format support when handling multisampled resource");

		if (!(support & D3D11_FORMAT_SUPPORT_MULTISAMPLE_RESOLVE))
			throw("Error no support when handling multisampled resource");
	}

	void HandleDepthResource(D3D11_TEXTURE2D_DESC& desc)
	{
		switch (desc.Format)
		{
			case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
			{
				desc.Format = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS; // Do not know if this is what it should be but seems like the best
				break;
			}
			case DXGI_FORMAT_D32_FLOAT:
			{
				desc.Format = DXGI_FORMAT_R32_FLOAT;
				break;
			}
			case DXGI_FORMAT_D24_UNORM_S8_UINT:
			{
				desc.Format = DXGI_FORMAT_R24G8_TYPELESS; // Do not know if this is what it should be but seems like the best
				break;
			}
			case DXGI_FORMAT_D16_UNORM:
			{
				desc.Format = DXGI_FORMAT_R16_UNORM;
				break;
			}
			default:
			{
				// If nothing of the above then we do not need to do anything
			}
		}
	}

	void CreateSharedTextureResource(ID3D11Resource* resource)
	{
		ID3D11Texture2D* texture = (ID3D11Texture2D*)resource;
		D3D11_TEXTURE2D_DESC desc;

		texture->GetDesc(&desc);
		desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;// _KEYEDMUTEX;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		ID3D11Texture2D* rtResource;
		if (desc.SampleDesc.Count > 1)
			HandleMultisampledResource(desc, rtResource);
		else
		{
			HandleDepthResource(desc);
			HRESULT hr = CreateTexture2DInternal(GlobalDevice, &desc, nullptr, &rtResource);
		}

		StoredResource toStore;
		HRESULT myResult;
		IDXGIResource* temp;
		myResult = rtResource->QueryInterface(__uuidof(IDXGIResource), (void**)&temp);
		if (myResult != S_OK)
			MessageBoxA(0, "Falied to create resource!", "", 0);
		myResult = temp->GetSharedHandle(&toStore.resourceHandle);
		if (myResult != S_OK)
			MessageBoxA(0, "Falied to get shared handle!", "", 0);

		toStore.originalResource = resource;
		toStore.replacementResource = resource;
		toStore.sharedResource = rtResource;

		storedResources[resource] = toStore;
		unsigned long handleValue = unsigned long(toStore.resourceHandle);
		jobHandler.ProduceJob(JobType::TEXTURE_JOB, unsigned long long(0) + handleValue);
	}

public:

	ID3D11Device* GetDevice()
	{
		return device;
	}
	
	static DeviceOverride* GetInstance();

	HRESULT Init(ID3D11Device* device)
	{
		this->device = device;
		//device->QueryInterface(__uuidof(ID3D11Device1), (void**)&device1);
		//device->QueryInterface(__uuidof(ID3D11Device2), (void**)&device2);
		//device->QueryInterface(__uuidof(ID3D11Device3), (void**)&device3);
		//device->QueryInterface(__uuidof(ID3D11Device4), (void**)&device4);
		//device->QueryInterface(__uuidof(ID3D11Device5), (void**)&device5);

		// Setup Hooks
		hook_CreateBuffer.SetupInterface(device, 3, reinterpret_cast<voidFunc>(CreateBuffer));
		hook_CreateTexture2D.SetupInterface(device, 5, reinterpret_cast<voidFunc>(CreateTexture2D));
		hook_CreateRenderTargetView.SetupInterface(device, 9, reinterpret_cast<voidFunc>(CreateRenderTargetView));
		hook_CreateDepthStencilView.SetupInterface(device, 10, reinterpret_cast<voidFunc>(CreateDepthStencilView));
		hook_CreateInputLayout.SetupInterface(device, 11, reinterpret_cast<voidFunc>(CreateInputLayout));
		hook_CreateVertexShader.SetupInterface(device, 12, reinterpret_cast<voidFunc>(CreateVertexShader));
		hook_CreateGeometryShader.SetupInterface(device, 13, reinterpret_cast<voidFunc>(CreateGeometryShader));
		hook_CreateGeometryShaderWithStreamOutput.SetupInterface(device, 14, reinterpret_cast<voidFunc>(CreateGeometryShaderWithStreamOutput));
		hook_CreatePixelShader.SetupInterface(device, 15, reinterpret_cast<voidFunc>(CreatePixelShader));
		hook_CreateHullShader.SetupInterface(device, 16, reinterpret_cast<voidFunc>(CreateHullShader));
		hook_CreateDomainShader.SetupInterface(device, 17, reinterpret_cast<voidFunc>(CreateDomainShader));
		hook_CreateComputeShader.SetupInterface(device, 18, reinterpret_cast<voidFunc>(CreateComputeShader));
		hook_CreateRasterizerState.SetupInterface(device, 22, reinterpret_cast<voidFunc>(CreateRasterizerState));

		return S_OK;
	}

	static HRESULT __stdcall CreateBuffer(ID3D11Device* device, const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
	{
		return DeviceOverride::GetInstance()->CreateBufferInternal(device, pDesc, pInitialData, ppBuffer);
	}

	HRESULT CreateBufferInternal(ID3D11Device* device, const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create buffer function was called!", "", 0);
		D3D11_Device_CreateBufferType oCreateBuffer = (D3D11_Device_CreateBufferType)hook_CreateBuffer.call;
		hook_CreateBuffer.Restore();
		hr = oCreateBuffer(device, pDesc, pInitialData, ppBuffer);
		hook_CreateBuffer.Inject();

		return hr;
	}

	static HRESULT __stdcall CreateTexture2D(ID3D11Device* device, const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
	{
		return DeviceOverride::GetInstance()->CreateTexture2DInternal(device, pDesc, pInitialData, ppTexture2D);
	}

	HRESULT CreateTexture2DInternal(ID3D11Device* device, const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create texture2D function was called!", "", 0);
		D3D11_Device_CreateTexture2D oCreateTexture2D = (D3D11_Device_CreateTexture2D)hook_CreateTexture2D.call;
		hook_CreateTexture2D.Restore();
		hr = oCreateTexture2D(device, pDesc, pInitialData, ppTexture2D);
		hook_CreateTexture2D.Inject();

		return hr;
	}

	static HRESULT __stdcall CreateRenderTargetView(ID3D11Device* device, ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, ID3D11RenderTargetView** ppRTView)
	{
		//MessageBoxA(0, "Render target function called!", "", 0);
		return DeviceOverride::GetInstance()->CreateRenderTargetViewInternal(device, pResource, pDesc, ppRTView);
	}

	HRESULT CreateRenderTargetViewInternal(ID3D11Device* device, ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, ID3D11RenderTargetView** ppRTView)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create render target view function was called!", "", 0);

		D3D11_Device_CreateRenderTargetView oCreateRenderTargetView = (D3D11_Device_CreateRenderTargetView)hook_CreateRenderTargetView.call;
		hook_CreateRenderTargetView.Restore();
		hr = oCreateRenderTargetView(device, pResource, pDesc, ppRTView);
		hook_CreateRenderTargetView.Inject();

		//CreateSharedTextureResource(pResource);

		return hr;
	}

	static HRESULT __stdcall CreateDepthStencilView(ID3D11Device* device, ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
	{
		return DeviceOverride::GetInstance()->CreateDepthStencilViewInternal(device, pResource, pDesc, ppDepthStencilView);
	}

	HRESULT CreateDepthStencilViewInternal(ID3D11Device* device, ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create depth stencil view function was called!", "", 0);
		D3D11_Device_CreateDepthStencilView oCreateDepthStencilView = (D3D11_Device_CreateDepthStencilView)hook_CreateDepthStencilView.call;
		hook_CreateDepthStencilView.Restore();
		hr = oCreateDepthStencilView(device, pResource, pDesc, ppDepthStencilView);
		hook_CreateDepthStencilView.Inject();

		//CreateSharedTextureResource(pResource);

		return hr;
	}

	static HRESULT __stdcall CreateInputLayout(ID3D11Device* device, const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout)
	{
		return DeviceOverride::GetInstance()->CreateInputLayoutInternal(device, pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
	}

	HRESULT CreateInputLayoutInternal(ID3D11Device* device, const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create input layout function was called!", "", 0);
		D3D11_Device_CreateInputLayout oCreateInputLayout = (D3D11_Device_CreateInputLayout)hook_CreateInputLayout.call;
		hook_CreateInputLayout.Restore();
		hr = oCreateInputLayout(device, pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
		hook_CreateInputLayout.Inject();

		return hr;
	}

	static HRESULT __stdcall CreateVertexShader(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader)
	{
		return DeviceOverride::GetInstance()->CreateVertexShaderInternal(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
	}

	HRESULT CreateVertexShaderInternal(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create vertex shader function was called!", "", 0);
		D3D11_Device_CreateVertexShaderType oCreateVertexShader = (D3D11_Device_CreateVertexShaderType)hook_CreateVertexShader.call;
		hook_CreateVertexShader.Restore();
		hr = oCreateVertexShader(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
		hook_CreateVertexShader.Inject();

		return hr;
	}

	static HRESULT __stdcall CreateGeometryShader(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11GeometryShader **ppGeometryShader)
	{
		return DeviceOverride::GetInstance()->CreateGeometryShaderInternal(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
	}

	HRESULT CreateGeometryShaderInternal(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11GeometryShader **ppGeometryShader)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create geometry shader function was called!", "", 0);
		D3D11_Device_CreateGeometryShaderType oCreateGeometryShader = (D3D11_Device_CreateGeometryShaderType)hook_CreateGeometryShader.call;
		hook_CreateGeometryShader.Restore();
		hr = oCreateGeometryShader(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
		hook_CreateGeometryShader.Inject();

		return hr;
	}

	static HRESULT __stdcall CreateGeometryShaderWithStreamOutput(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, const UINT* pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader)
	{
		return DeviceOverride::GetInstance()->CreateGeometryShaderWithStreamOutputInternal(device, pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
	}

	HRESULT CreateGeometryShaderWithStreamOutputInternal(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, const UINT* pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create geometry shader with stream output function was called!", "", 0);
		D3D11_Device_CreateGeometryShaderWithStreamOutputType oCreateGeometryShaderWithOutput = (D3D11_Device_CreateGeometryShaderWithStreamOutputType)hook_CreateGeometryShaderWithStreamOutput.call;
		hook_CreateGeometryShaderWithStreamOutput.Restore();
		hr = oCreateGeometryShaderWithOutput(device, pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
		hook_CreateGeometryShaderWithStreamOutput.Inject();

		return hr;
	}

	static HRESULT __stdcall CreatePixelShader(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11PixelShader **ppPixelShader)
	{
		return DeviceOverride::GetInstance()->CreatePixelShaderInternal(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
	}

	HRESULT CreatePixelShaderInternal(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11PixelShader **ppPixelShader)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create pixel shader function was called!", "", 0);
		D3D11_Device_CreatePixelShaderType oCreatePixelShader = (D3D11_Device_CreatePixelShaderType)hook_CreatePixelShader.call;
		hook_CreatePixelShader.Restore();
		hr = oCreatePixelShader(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
		hook_CreatePixelShader.Inject();

		return hr;
	}

	static HRESULT __stdcall CreateHullShader(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11HullShader** ppHullShader)
	{
		return DeviceOverride::GetInstance()->CreateHullShaderInternal(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
	}

	HRESULT CreateHullShaderInternal(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11HullShader** ppHullShader)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create hull shader function was called!", "", 0);
		D3D11_Device_CreateHullShaderType oCreateHullShader = (D3D11_Device_CreateHullShaderType)hook_CreateHullShader.call;
		hook_CreateHullShader.Restore();
		hr = oCreateHullShader(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
		hook_CreateHullShader.Inject();

		return hr;
	}

	static HRESULT __stdcall CreateDomainShader(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11DomainShader **ppDomainShader)
	{
		return DeviceOverride::GetInstance()->CreateDomainShaderInternal(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
	}

	HRESULT CreateDomainShaderInternal(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11DomainShader **ppDomainShader)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create domain shader function was called!", "", 0);
		D3D11_Device_CreateDomainShaderType oCreateDomainShader = (D3D11_Device_CreateDomainShaderType)hook_CreateDomainShader.call;
		hook_CreateDomainShader.Restore();
		hr = oCreateDomainShader(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
		hook_CreateDomainShader.Inject();

		return hr;
	}

	static HRESULT __stdcall CreateComputeShader(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11ComputeShader **ppComputeShader)
	{
		return DeviceOverride::GetInstance()->CreateComputeShaderInternal(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
	}

	HRESULT CreateComputeShaderInternal(ID3D11Device* device, const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11ComputeShader **ppComputeShader)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create compute shader function was called!", "", 0);
		D3D11_Device_CreateComputeShaderType oCreateComputeShader = (D3D11_Device_CreateComputeShaderType)hook_CreateComputeShader.call;
		hook_CreateComputeShader.Restore();
		hr = oCreateComputeShader(device, pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
		hook_CreateComputeShader.Inject();

		return hr;
	}

	static HRESULT __stdcall CreateRasterizerState(ID3D11Device* device, const D3D11_RASTERIZER_DESC *pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
	{
		return DeviceOverride::GetInstance()->CreateRasterizerStateInternal(device, pRasterizerDesc, ppRasterizerState);
	}

	HRESULT CreateRasterizerStateInternal(ID3D11Device* device, const D3D11_RASTERIZER_DESC *pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
	{
		HRESULT hr = S_OK;
		//MessageBoxA(0, "My create rasterizer state function was called!", "", 0);
		RasterizerStateData data;
		D3D11_RASTERIZER_DESC wireFrame;
		memcpy(&wireFrame, pRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		wireFrame.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		D3D11_Device_CreateRasterizerStateType oCreateRasterizerState = (D3D11_Device_CreateRasterizerStateType)hook_CreateRasterizerState.call;
		hook_CreateRasterizerState.Restore();

		//auto before = *ppRasterizerState;
		//MessageBoxA(0, ("Before :" + std::to_string((unsigned int)*ppRasterizerState)).c_str(), "", 0);
		hr = oCreateRasterizerState(device, pRasterizerDesc, ppRasterizerState);
		//MessageBoxA(0, ("After :" + std::to_string((unsigned int)*ppRasterizerState)).c_str(), "", 0);

		//if(before == *ppRasterizerState)
		//	MessageBoxA(0, "Same!", "", 0);
		//else
		//	MessageBoxA(0, "Changed!", "", 0);

		oCreateRasterizerState(device, &wireFrame, &data.wireframe);
		data.original = *ppRasterizerState;
		hook_CreateRasterizerState.Inject();
		rData.push_back(data);

		return hr;
	}

};

DeviceOverride* DeviceOverride::instance = nullptr;
DeviceOverride* DeviceOverride::GetInstance()
{
	if (!instance)
		instance = new DeviceOverride();

	return instance;
}