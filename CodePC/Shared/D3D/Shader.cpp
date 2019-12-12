#include "Shader.h"
#include "Device3D.h"

Shader::Shader()
{
	m_pEffect = NULL;
	m_pTechnique = NULL;
	m_pInputLayout = NULL;
}

Shader::~Shader()
{
	SAFE_RELEASE(m_pInputLayout);
	//SAFE_RELEASE(m_pEffect);

	if(m_pEffect)
	{
		while(m_pEffect->Release());
		m_pEffect = NULL;
	}
}

HRESULT Shader::Init(Device3D* device3D, const TCHAR* filename,
		const D3D11_INPUT_ELEMENT_DESC* inputElementDesc, unsigned int numElements)
{
	mDevice3D = device3D;

	HRESULT hr = S_OK;

	ID3DBlob*	pBlobEffect = NULL;
	ID3DBlob*	pBlobErrors = NULL;
	
	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
	dwShaderFlags |= D3D10_SHADER_DEBUG;
#endif

	hr = D3DX11CompileFromFile(
		filename,
		NULL,
		NULL,
		"",
		"fx_5_0",
		dwShaderFlags,
		NULL,
		NULL,
		&pBlobEffect,
		&pBlobErrors,
		NULL
		);

	char* l_pError = NULL;
	if( FAILED(hr) )
	{
		char msg[20000];
		strcpy_s(msg, sizeof(msg), (char*)pBlobErrors->GetBufferPointer());
		OutputDebugStringA(msg);
		MessageBoxA(GetDesktopWindow(), msg, "Effect compilation error", MB_OK | MB_ICONERROR);
		return hr;
	}

	if(FAILED(hr = D3DX11CreateEffectFromMemory(
		pBlobEffect->GetBufferPointer(),
		pBlobEffect->GetBufferSize(),
		dwShaderFlags,
		mDevice3D->GetDevice(),
		&m_pEffect
		)))
	{
		MessageBox(0, _T("Cannot create effect from memory."), _T("D3DX11CreateEffectFromMemory error"), MB_OK | MB_ICONERROR);
		return hr;
	}


	m_pTechnique = m_pEffect->GetTechniqueByIndex(0);


	if(inputElementDesc)
	{
		D3DX11_PASS_DESC PassDesc;
		m_pTechnique->GetPassByIndex(0)->GetDesc(&PassDesc);
		if(FAILED(hr = mDevice3D->GetDevice()->CreateInputLayout(
			inputElementDesc,
			numElements,
			PassDesc.pIAInputSignature,
			PassDesc.IAInputSignatureSize,
			&m_pInputLayout
			)))
		{
			MessageBox(0, _T("Cannot create input layout."), _T("CreateInputLayout error"), MB_OK | MB_ICONERROR);
			return hr;
		}
	}

	return hr;
}

HRESULT Shader::Apply(unsigned int pass)
{
	ID3DX11EffectPass* p = m_pTechnique->GetPassByIndex(pass);
	if(p)
	{
		p->Apply(0, mDevice3D->GetDeviceContext());

		if(m_pInputLayout)
		{
			mDevice3D->GetDeviceContext()->IASetInputLayout(m_pInputLayout);
		}
		return S_OK;
	}

	return E_FAIL;
}

void Shader::SetFloat(char* variable, float value)
{
	m_pEffect->GetVariableByName(variable)->AsScalar()->SetFloat(value);
}

void Shader::SetMatrix(char* variable, const D3DXMATRIX& mat)
{
	m_pEffect->GetVariableByName(variable)->AsMatrix()->SetMatrix((float*)&mat);
}

void Shader::SetMatrixArray(char* variable, const float* data, unsigned int offset, unsigned int count)
{
	m_pEffect->GetVariableByName(variable)->AsMatrix()->SetMatrixArray(data, offset, count);
}

void Shader::SetFloat4(char* variable, D3DXVECTOR4 value)
{
	m_pEffect->GetVariableByName(variable)->AsVector()->SetFloatVector((float*)&value);
}

void Shader::SetResource(char* variable, ID3D11ShaderResourceView* value)
{
	m_pEffect->GetVariableByName(variable)->AsShaderResource()->SetResource(value);
}

void Shader::SetUnorderedAccessView(char* variable, ID3D11UnorderedAccessView* value)
{
	m_pEffect->GetVariableByName(variable)->AsUnorderedAccessView()->SetUnorderedAccessView(value);
}

void Shader::SetInt(char* variable, int value)
{
	m_pEffect->GetVariableByName(variable)->AsScalar()->SetInt(value);
}

void Shader::SetBool(char* variable, bool value)
{
	m_pEffect->GetVariableByName(variable)->AsScalar()->SetBool(value);
}

void Shader::SetRawData(char* variable, void* data, size_t size)
{
	m_pEffect->GetVariableByName(variable)->SetRawValue(data, 0, (UINT)size);
}

ID3DX11Effect* Shader::GetEffect()
{
	return m_pEffect;
}