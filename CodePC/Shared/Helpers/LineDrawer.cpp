#include "LineDrawer.h"

#include "../D3D/Device3D.h"
#include "../D3D/Buffer.h"
#include "../D3D/Shader.h"

LineDrawer::LineDrawer()
{
	mHasChanged = false;
	mPermanent = false;
}

LineDrawer::~LineDrawer()
{
	SAFE_DELETE(mVB);
}

void LineDrawer::SetPermanent(bool permanent)
{
	mPermanent = permanent;
}

bool LineDrawer::GetPermanent()
{
	return mPermanent;
}

bool LineDrawer::Init(Device3D* device3D, int capacity)
{
	mDevice3D = device3D;
	mCapacity = capacity * 2;

	//Create input layout for the FBX scene
	const D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION",			  0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",				  0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	int iNumElements = sizeof(inputDesc)/sizeof(D3D10_INPUT_ELEMENT_DESC);
	
	static Shader* s = 0;

	mShader = myNew Shader();
	if(FAILED(mShader->Init(mDevice3D, _T("../Shaders/Lines.fx"), inputDesc, iNumElements)))
		return false;


	BUFFER_INIT_DESC d;
	d.ElementSize = sizeof(LINE_VERTEX);
	d.InitData = NULL;
	d.NumElements = mCapacity;
	d.Type = VERTEX_BUFFER;
	d.Usage = BUFFER_CPU_WRITE_DISCARD;

	mVB = myNew Buffer();
	if(FAILED(mVB->Init(mDevice3D, d)))
	{
		SAFE_DELETE(mVB);
		return false;
	}

	return true;
}

bool LineDrawer::AddLine(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXVECTOR3 color)
{
	if((int)mLines.size() < mCapacity)
	{
		LINE_VERTEX v0 = { start, color };
		mLines.push_back(v0);
		LINE_VERTEX v1 = { end, color };
		mLines.push_back(v1);

		mHasChanged = true;

		return true;
	}
	return false;
}

void LineDrawer::Render(D3DXMATRIX worldViewProj)
{
	mDevice3D->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	mShader->SetMatrix("gWVP", worldViewProj);
	mShader->Apply(0);

	if(mHasChanged)
	{
		void* v = mVB->Map();
		if(v)
		{
			memcpy(v, &mLines[0], sizeof(LINE_VERTEX) * mLines.size());
			mVB->Unmap();

			mHasChanged = false;
		}
	}

	mVB->Apply();

	mDevice3D->GetDeviceContext()->Draw(mLines.size(), 0);

	if(GetPermanent() == false)
		mLines.clear();
}
