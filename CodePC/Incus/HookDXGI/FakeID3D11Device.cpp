#include "FakeID3D11Device.hpp"
/*
FakeID3D11Device::~FakeID3D11Device()
{

}

ULONG __stdcall FakeID3D11Device::AddRef()
{
	return realDevice->AddRef();
}

HRESULT __stdcall FakeID3D11Device::QueryInterface(REFIID riid, void ** ppvObject)
{
	return realDevice->QueryInterface(riid, ppvObject);
}

ULONG __stdcall FakeID3D11Device::Release()
{
	return realDevice->Release();
}

HRESULT FakeID3D11Device::CheckCounter(const D3D11_COUNTER_DESC * pDesc, D3D11_COUNTER_TYPE * pType, UINT * pActiveCounters, LPSTR szName, UINT * pNameLength, LPSTR szUnits, UINT * pUnitsLength, LPSTR szDescription, UINT * pDescriptionLength)
{
	return this->;
}
*/

HRESULT __stdcall FakeID3D11Device::CreateVertexShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11VertexShader ** ppVertexShader)
{
	info.numberOfCreatedVertexShaders++;
	return this->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
}
