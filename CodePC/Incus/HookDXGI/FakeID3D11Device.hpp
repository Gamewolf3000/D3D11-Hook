#include <d3d11_4.h>
#include <utility>
#include <cstdint>

struct DeviceInfo
{
	std::uint_fast32_t numberOfCreatedContexts = 0;
	std::uint_fast32_t numberOfCreatedVertexShaders = 0;
	std::uint_fast32_t numberOfCreatedHullShaders = 0;
	std::uint_fast32_t numberOfCreatedDomainShaders = 0;
	std::uint_fast32_t numberOfCreatedGeometryShaders = 0;
	std::uint_fast32_t numberOfCreatedPixelShaders = 0;
	std::uint_fast32_t numberOfCreatedRasterizerStates = 0;
};

class FakeID3D11Device : public ID3D11Device5
{
private:
	//ID3D11Device5* realDevice;

public:
	FakeID3D11Device(ID3D11Device5* real) : ID3D11Device5(std::move(*real)) {};//, realDevice(real) {};
	//FakeID3D11Device(const FakeID3D11Device& other) : ID3D11Device5(other) {};
	//FakeID3D11Device(FakeID3D11Device&& other) : ID3D11Device5(std::move(other)) {};
	//FakeID3D11Device& operator=(const FakeID3D11Device& other);
	//FakeID3D11Device& operator=(FakeID3D11Device&& other);
	virtual ~FakeID3D11Device() {};

	DeviceInfo info;

	/*
	// IUnknown methods
	ULONG __stdcall AddRef() override;
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	template<typename Q>
	HRESULT STDMETHODCALLTYPE QueryInterface(_COM_Outptr_ Q** pp) override;
	ULONG __stdcall Release() override;
	*/

	// ID3D11Device methods

	HRESULT __stdcall CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader) override;
};

/*
template<typename Q>
inline HRESULT __stdcall FakeID3D11Device::QueryInterface(_COM_Outptr_ Q ** pp)
{
	return QueryInterface(__uuidof(Q), (void **)pp);
}
*/