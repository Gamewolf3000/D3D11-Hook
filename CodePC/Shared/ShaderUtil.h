
#include <d3dCompiler.h>
#include <d3d11_3.h>
#pragma comment(lib, "d3dcompiler.lib")

#include <string>
#include <fstream>
#include <sstream>

// Safe release for interfaces
template<class Interface>
inline void SafeRelease2(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != nullptr)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = nullptr;
	}
}

static HRESULT CompileShader(LPCSTR shaderFile, LPCSTR pEntrypoint, LPCSTR pTarget, CONST D3D_SHADER_MACRO* pDefines, ID3DBlob** pCompiledShader)
{
	DWORD dwShaderFlags =
#ifdef _DEBUG
		D3DCOMPILE_DEBUG |
		D3DCOMPILE_OPTIMIZATION_LEVEL0 |
#else
		D3DCOMPILE_OPTIMIZATION_LEVEL3 |
#endif
		D3DCOMPILE_ENABLE_STRICTNESS |
		D3DCOMPILE_IEEE_STRICTNESS;

	std::string shader_code;
	std::ifstream in(shaderFile, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		shader_code.resize((unsigned int)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&shader_code[0], shader_code.size());
		in.close();
	}

	ID3DBlob* pErrorBlob = nullptr;
	HRESULT hr = D3DCompile(
		shader_code.data(),
		shader_code.size(),
		shaderFile,
		pDefines,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		pEntrypoint,
		pTarget,
		dwShaderFlags,
		0,
		pCompiledShader,
		&pErrorBlob);

	if (pErrorBlob)
	{
		OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		SafeRelease2(pErrorBlob);
	}

	return hr;
}

static ID3D11VertexShader* CompileVSFromFile(ID3D11Device* device,
	LPCSTR path,
	LPCSTR functionName = "VS",
	LPCSTR profile = "vs_5_0",
	CONST D3D_SHADER_MACRO* defines = NULL,
	ID3DBlob** byteCode = NULL)
{
	ID3D11VertexShader* pShader = nullptr;
	ID3DBlob* pShaderBinary = nullptr;
	if (SUCCEEDED(CompileShader(path, functionName, profile, defines, &pShaderBinary)))
	{
		device->CreateVertexShader(
			pShaderBinary->GetBufferPointer(),
			pShaderBinary->GetBufferSize(),
			nullptr,
			&pShader);

		if (byteCode != nullptr)
			*byteCode = pShaderBinary;
		else
			SafeRelease2(pShaderBinary);
	}

	return pShader;
}

static ID3D11PixelShader* CompilePSFromFile(ID3D11Device* device,
	LPCSTR path,
	LPCSTR functionName = "PS",
	LPCSTR profile = "ps_5_0",
	CONST D3D_SHADER_MACRO* defines = nullptr)
{
	ID3D11PixelShader* pShader = nullptr;
	ID3DBlob* pShaderBinary = nullptr;
	if (SUCCEEDED(CompileShader(path, functionName, profile, defines, &pShaderBinary)))
	{
		device->CreatePixelShader(
			pShaderBinary->GetBufferPointer(),
			pShaderBinary->GetBufferSize(),
			nullptr,
			&pShader);

		SafeRelease2(pShaderBinary);
	}

	return pShader;
}

static ID3D11GeometryShader* CompileGSFromFile(ID3D11Device* device,
	LPCSTR path,
	LPCSTR functionName = "GS",
	LPCSTR profile = "gs_5_0",
	CONST D3D_SHADER_MACRO* defines = nullptr)
{
	ID3D11GeometryShader* pShader = nullptr;
	ID3DBlob* pShaderBinary = nullptr;
	if (SUCCEEDED(CompileShader(path, functionName, profile, defines, &pShaderBinary)))
	{
		device->CreateGeometryShader(
			pShaderBinary->GetBufferPointer(),
			pShaderBinary->GetBufferSize(),
			nullptr,
			&pShader);

		SafeRelease2(pShaderBinary);
	}

	return pShader;
}

static ID3D11ComputeShader* CompileCSFromFile(ID3D11Device* device,
	LPCSTR path,
	LPCSTR functionName = "CS",
	LPCSTR profile = "cs_5_0",
	CONST D3D_SHADER_MACRO* defines = nullptr)
{
	ID3D11ComputeShader* pShader = nullptr;
	ID3DBlob* pShaderBinary = nullptr;
	if (SUCCEEDED(CompileShader(path, functionName, profile, defines, &pShaderBinary)))
	{
		device->CreateComputeShader(
			pShaderBinary->GetBufferPointer(),
			pShaderBinary->GetBufferSize(),
			nullptr,
			&pShader);

		SafeRelease2(pShaderBinary);
	}

	return pShader;
}

class CompileOptions
{
public:

	// constants
	static const UINT32 MaxDefines = 16;
	static const UINT32 BufferSize = 1024;

	CompileOptions();

	void Add(const std::string& name, UINT32 value);
	void Reset();

	const D3D10_SHADER_MACRO* Defines() const;

protected:

	D3D_SHADER_MACRO defines[MaxDefines + 1];
	CHAR buffer[BufferSize];
	UINT32 numDefines;
	UINT32 bufferIdx;
};

// Compute shader helpers
UINT32 DispatchSize(UINT32 tgSize, UINT32 numElements);
void SetCSInputs(ID3D11DeviceContext* context, ID3D11ShaderResourceView* srv0, ID3D11ShaderResourceView* srv1 = NULL,
	ID3D11ShaderResourceView* srv2 = NULL, ID3D11ShaderResourceView* srv3 = NULL);
void ClearCSInputs(ID3D11DeviceContext* context);
void SetCSOutputs(ID3D11DeviceContext* context, ID3D11UnorderedAccessView* uav0, ID3D11UnorderedAccessView* uav1 = NULL,
	ID3D11UnorderedAccessView* uav2 = NULL, ID3D11UnorderedAccessView* uav3 = NULL,
	ID3D11UnorderedAccessView* uav4 = NULL, ID3D11UnorderedAccessView* uav5 = NULL);
void ClearCSOutputs(ID3D11DeviceContext* context);
void SetCSSamplers(ID3D11DeviceContext* context, ID3D11SamplerState* sampler0, ID3D11SamplerState* sampler1 = NULL,
	ID3D11SamplerState* sampler2 = NULL, ID3D11SamplerState* sampler3 = NULL);
void SetCSShader(ID3D11DeviceContext* context, ID3D11ComputeShader* shader);