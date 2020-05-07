#pragma once
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <vector>
#include <algorithm>

#include "FakeID3D11Device.hpp"
#include "FakeID3D11DeviceContext.h"
#include "FakeIDXGIFactory.h"
#include "FakeIDXGISwapChain.h"

HRESULT __stdcall QueryInterface(REFIID riid, void ** ppvObject, IUnknown* calledOn)
{
	static const std::vector<GUID> deviceIds = { __uuidof(ID3D11Device), __uuidof(ID3D11Device1), __uuidof(ID3D11Device2),
												 __uuidof(ID3D11Device3), __uuidof(ID3D11Device4), __uuidof(ID3D11Device5)};
	static const std::vector<GUID> deviceContextIds = { __uuidof(ID3D11DeviceContext), __uuidof(ID3D11DeviceContext1), __uuidof(ID3D11DeviceContext2),
														__uuidof(ID3D11DeviceContext3), __uuidof(ID3D11DeviceContext4)};
	static const std::vector<GUID> factoryIds = { __uuidof(IDXGIFactory), __uuidof(IDXGIFactory1), __uuidof(IDXGIFactory2), __uuidof(IDXGIFactory3),
												 __uuidof(IDXGIFactory4), __uuidof(IDXGIFactory5), __uuidof(IDXGIFactory6) };
	static const std::vector<GUID> scIds = { __uuidof(IDXGISwapChain), __uuidof(IDXGISwapChain1), __uuidof(IDXGISwapChain2), __uuidof(IDXGISwapChain3),
											__uuidof(IDXGISwapChain4) };

	HRESULT hr = calledOn->QueryInterface(riid, ppvObject);

	if (FAILED(hr))
		return hr;

	if (std::find(deviceIds.begin(), deviceIds.end(), riid) != deviceIds.end())
	{
		*ppvObject = new FakeID3D11Device(static_cast<ID3D11Device*>(*ppvObject));
	}
	else if (std::find(deviceContextIds.begin(), deviceContextIds.end(), riid) != deviceContextIds.end())
	{
		FakeID3D11Device* creator;
		static_cast<FakeID3D11DeviceContext*>(calledOn)->GetDevice(&creator);
		*ppvObject = new FakeID3D11DeviceContext(static_cast<ID3D11DeviceContext*>(*ppvObject), creator);
	}
}