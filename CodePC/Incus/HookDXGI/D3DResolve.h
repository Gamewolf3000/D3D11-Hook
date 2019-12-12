#pragma once

#include <d3d11_4.h>
#include <stdafx.h>

class D3DResolve
{
public:
	virtual ~D3DResolve() {};
	virtual HRESULT Init(IUnknown* device) = 0;
	virtual HRESULT Resolve(IDXGISwapChain* swap_chain_src, IDXGISwapChain1* swap_chain_dest) = 0;
};

class D3D11Resolve : public D3DResolve
{
	ID3D11Device* device_;
	ID3D11DeviceContext* device_context_;
public:
	D3D11Resolve()
	{
		device_ = nullptr;
		device_context_ = nullptr;
	}

	~D3D11Resolve()
	{
		SAFE_RELEASE(device_);
		SAFE_RELEASE(device_context_);
	}

	virtual HRESULT Init(IUnknown* device)
	{
		HRESULT hr = S_OK;
		if (SUCCEEDED(hr = device->QueryInterface(__uuidof(ID3D11Device), (void**)&device_))) // See if there already exist a device?
		{
			device_->GetImmediateContext(&device_context_); // Get the devicecontext that belongs to it?
		}

		return hr; // Should we not check if we succeeded?
	}

	virtual HRESULT Resolve(IDXGISwapChain* swap_chain_src, IDXGISwapChain1* swap_chain_dest)
	{
		HRESULT hr = S_OK;
		ID3D11Texture2D* pSrc = nullptr;
		ID3D11Texture2D* pDst = nullptr;
		if (SUCCEEDED(hr = swap_chain_src->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pSrc))) // Get existing swap chain?
		{
			if (SUCCEEDED(hr = swap_chain_dest->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pDst))) // Get another swap chain that already exist?
			{
				DXGI_SWAP_CHAIN_DESC swap_chain_desc;
				if (SUCCEEDED(hr = swap_chain_src->GetDesc(&swap_chain_desc))) // Get the description of the first swap chain
				{
					if (swap_chain_desc.SampleDesc.Count != 1 || swap_chain_desc.SampleDesc.Quality != 0)
						device_context_->ResolveSubresource(pDst, 0, pSrc, 0, swap_chain_desc.BufferDesc.Format); // Copy settings, but do it differently if the multisampling is more than 1?
					else
						device_context_->CopyResource(pDst, pSrc); // Copy settings?
				}

				SAFE_RELEASE(pDst);
			}

			SAFE_RELEASE(pSrc);
		}

		return hr;
	}
};