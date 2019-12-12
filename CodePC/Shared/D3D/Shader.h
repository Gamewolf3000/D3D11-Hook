#ifndef SHADER__H
#define SHADER__H

#include <stdafx.h>

class Shader
{

	class Device3D*			mDevice3D;
	ID3D11InputLayout*		m_pInputLayout;

	ID3DX11Effect* m_pEffect;
	ID3DX11EffectTechnique* m_pTechnique;

public:
	Shader();
	~Shader();

	HRESULT Init(class Device3D* device3D, const TCHAR* filename,
		const D3D11_INPUT_ELEMENT_DESC* inputElementDesc, unsigned int numElements);

	HRESULT Apply(unsigned int pass);

	void SetMatrix(char* variable, const D3DXMATRIX& mat);
	void SetMatrixArray(char* variable, const float* data, unsigned int offset, unsigned int count);
	void SetFloat(char* variable, float value);
	void SetFloat4(char* variable, D3DXVECTOR4 value);

	void SetInt(char* variable, int value);
	void SetBool(char* variable, bool value);
	void SetRawData(char* variable, void* data, size_t size);

	void SetResource(char* variable, ID3D11ShaderResourceView* value);
	void SetUnorderedAccessView(char* variable, ID3D11UnorderedAccessView* value);

	ID3DX11Effect* GetEffect();


	ID3D11InputLayout* GetInputLayout() { return m_pInputLayout; } // <<--------- TEMP!!!!!!!!!!!!!!!!!!!!
};

#endif
