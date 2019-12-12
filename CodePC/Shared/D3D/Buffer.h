#ifndef BUFFER__H
#define BUFFER__H

#include <stdafx.h>

enum BUFFER_TYPE
{
	VERTEX_BUFFER,
	INDEX_BUFFER,
	CONSTANT_BUFFER_VS,
	CONSTANT_BUFFER_GS,
	CONSTANT_BUFFER_PS,
	BUFFER_TYPE_COUNT
};

enum BUFFER_USAGE
{
	BUFFER_DEFAULT,
	BUFFER_STREAM_OUT_TARGET,
	BUFFER_CPU_WRITE,
	BUFFER_CPU_WRITE_DISCARD,
	BUFFER_CPU_READ,
	BUFFER_USAGE_COUNT
};

struct BUFFER_INIT_DESC
{
	BUFFER_TYPE		Type;
	UINT32			NumElements;
	UINT32			ElementSize;
	BUFFER_USAGE	Usage;
	void*			InitData;

	BUFFER_INIT_DESC()
	{
		InitData = NULL;
	}
};

class Buffer
{
protected:
	ID3D11Buffer*	mBuffer;
	BUFFER_TYPE		mType;
	BUFFER_USAGE	mUsage;

	UINT32			mElementSize;
	UINT32			mElementCount;

	class Device3D*	mDevice3D;
public:
	Buffer();
	virtual ~Buffer();

	HRESULT Init(class Device3D* device3D, BUFFER_INIT_DESC& initDesc);

	void* Map();
	void Unmap();

	HRESULT Apply(UINT32 misc = 0);

	ID3D11Buffer* GetBufferPointer();
	UINT32 GetVertexSize();
	UINT32 GetElementCount();
};

#endif
