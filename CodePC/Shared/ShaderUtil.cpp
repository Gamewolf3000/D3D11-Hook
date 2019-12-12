#include "ShaderUtil.h"

// Computes a compute shader dispatch size given a thread group size, and number of elements to process
UINT32 DispatchSize(UINT32 tgSize, UINT32 numElements)
{
	UINT32 dispatchSize = numElements / tgSize;
	dispatchSize += numElements % tgSize > 0 ? 1 : 0;
	return dispatchSize;
}

void SetCSInputs(ID3D11DeviceContext* context, ID3D11ShaderResourceView* srv0, ID3D11ShaderResourceView* srv1,
	ID3D11ShaderResourceView* srv2, ID3D11ShaderResourceView* srv3)
{
	ID3D11ShaderResourceView* srvs[4] = { srv0, srv1, srv2, srv3 };
	context->CSSetShaderResources(0, 4, srvs);
}

void ClearCSInputs(ID3D11DeviceContext* context)
{
	SetCSInputs(context, NULL, NULL, NULL, NULL);
}

void SetCSOutputs(ID3D11DeviceContext* context, ID3D11UnorderedAccessView* uav0, ID3D11UnorderedAccessView* uav1,
	ID3D11UnorderedAccessView* uav2, ID3D11UnorderedAccessView* uav3, ID3D11UnorderedAccessView* uav4,
	ID3D11UnorderedAccessView* uav5)
{
	ID3D11UnorderedAccessView* uavs[6] = { uav0, uav1, uav2, uav3, uav4, uav5 };
	context->CSSetUnorderedAccessViews(0, 6, uavs, NULL);
}

void ClearCSOutputs(ID3D11DeviceContext* context)
{
	SetCSOutputs(context, NULL, NULL, NULL, NULL);
}

void SetCSSamplers(ID3D11DeviceContext* context, ID3D11SamplerState* sampler0, ID3D11SamplerState* sampler1,
	ID3D11SamplerState* sampler2, ID3D11SamplerState* sampler3)
{
	ID3D11SamplerState* samplers[4] = { sampler0, sampler1, sampler2, sampler3 };
	context->CSSetSamplers(0, 4, samplers);
}

void SetCSShader(ID3D11DeviceContext* context, ID3D11ComputeShader* shader)
{
	context->CSSetShader(shader, NULL, 0);
}



// == CompileOptions ==============================================================================

CompileOptions::CompileOptions()
{
	Reset();
}

void CompileOptions::Add(const std::string& name, UINT32 value)
{
	_ASSERT(numDefines < MaxDefines);

	defines[numDefines].Name = buffer + bufferIdx;
	for (UINT32 i = 0; i < name.length(); ++i)
		buffer[bufferIdx++] = name[i];
	++bufferIdx;

	// convert number to an ansi string
	std::ostringstream stream;
	stream << value;

	std::string stringVal = stream.str();
	defines[numDefines].Definition = buffer + bufferIdx;
	for (UINT32 i = 0; i < stringVal.length(); ++i)
		buffer[bufferIdx++] = stringVal[i];
	++bufferIdx;

	++numDefines;
}

void CompileOptions::Reset()
{
	numDefines = 0;
	bufferIdx = 0;

	for (UINT32 i = 0; i < MaxDefines; ++i)
	{
		defines[i].Name = NULL;
		defines[i].Definition = NULL;
	}

	ZeroMemory(buffer, BufferSize);
}

const D3D_SHADER_MACRO* CompileOptions::Defines() const
{
	return defines;
}