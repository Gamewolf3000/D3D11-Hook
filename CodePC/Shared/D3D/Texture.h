#ifndef _TEXTURE__H
#define _TEXTURE__H

#include <stdafx.h>

class Texture
{
public:
	Texture();
	~Texture();

	//HRESULT Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* filename);
	HRESULT Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int width, int height, bool mappable = false, void* initData = NULL);
	void Release();
	ID3D11ShaderResourceView* GetResource();

	float GetWidth();
	float GetHeight();

	void	UpdateData(void* data, ID3D11DeviceContext* deviceContext = NULL, D3D11_BOX* pDestRegion = NULL);

	void*	Map(ID3D11DeviceContext* deviceContext = 0);
	void	Unmap();

	const char* GetFilename();

private:
	ID3D11DeviceContext* mDeviceContext;
	ID3D11Device*		 mDevice;
public:
	ID3D11DeviceContext* mDeviceContextUsedToLock;

	ID3D11ShaderResourceView* m_pTextureView;
	ID3D11Texture2D* m_pTexture;

	float	m_iTextureWidth;
	float	m_iTextureHeight;
	char	m_cFilename[MAX_PATH];
};

#endif
