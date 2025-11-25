#pragma once

class VertexShader
{
public:
	void CreateVertexShader(LPCWSTR pFileName, LPCSTR pEntrypoint, LPCSTR pTarget);
	void SetToVS();
private:
	wstring path = L"_Shaders/Texture.hlsl";
	ComPtr<ID3D11InputLayout> inputLayout;
	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3D11VertexShader> vertexShader;
};

void VertexShader::CreateVertexShader(LPCWSTR pFileName, LPCSTR pEntrypoint, LPCSTR pTarget)
{
	HRESULT hr = D3DCompileFromFile
	(
		pFileName,
		nullptr,
		nullptr,
		pEntrypoint,
		pTarget,
		0,
		0,
		&vsBlob,
		nullptr
	);
	CHECK(hr);

	vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HRESULT hr = DEVICE->CreateInputLayout
	(
		layoutDesc.data(),
		UINT(layoutDesc.size()),
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&inputLayout
	);
	CHECK(hr);

	HRESULT hr = DEVICE->CreateVertexShader
	(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		nullptr,
		&vertexShader
	);
	CHECK(hr);
}

inline void VertexShader::SetToVS()
{

}
