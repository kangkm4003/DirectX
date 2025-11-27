#include "stdafx.h"
#include "Program.h"

Program::Program()
{
	// vertexData (삼각형모양으로 픽셀 지정하기)
	{
		vertices.assign(3, VertexColor());
		vertices[0].position = { -0.5f, -0.5f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[2].position = { 0.5f, -0.5f };
	}
	for (auto& vertex : vertices)
	{
		vertex.color = { 1.0f, 0.0f, 0.0f, 1.0f };
	}

	// vertexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(vertices[0]) * (UINT)vertices.size();
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride;

		D3D11_SUBRESOURCE_DATA subData;
		subData.pSysMem = vertices.data();
		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData,&vertexBuffer);
		CHECK(hr);
	}
	// vsBlob

	{
		HRESULT hr = D3DCompileFromFile
		(
			L"_Shaders/Color.hlsl",
			nullptr,
			nullptr,
			"VS",
			"vs_5_0",
			0,
			0,
			&vsBlob,
			nullptr
		);
		CHECK(hr);
	}

	// inputLayoutDesc
	{
		vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
	}

	// vertexShader
	{
		HRESULT hr = DEVICE->CreateVertexShader
		(
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			nullptr,
			&vertexShader
		);
		CHECK(hr);
	}

	// pixelShader
	{
		HRESULT hr = D3DCompileFromFile
		(
			L"_Shaders/Color.hlsl",
			nullptr,
			nullptr,
			"PS",
			"ps_5_0",
			0,
			0,
			&psBlob,
			nullptr
		);
		CHECK(hr);

		hr = DEVICE->CreatePixelShader
		(
			psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(),
			nullptr,
			&pixelShader
		);
		CHECK(hr);
	}
}

Program::~Program()
{

}

void Program::Update()
{
	
}

void Program::Render()
{
	UINT stride = sizeof(vertices[0]);
	UINT offset = 0;

	//IA
	DEVICECONTEXT->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetInputLayout(inputLayout.Get());
	DEVICECONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//VS
	DEVICECONTEXT->VSSetShader(vertexShader.Get(), nullptr, 0);

	//PS
	DEVICECONTEXT->PSSetShader(pixelShader.Get(), nullptr, 0);

	DEVICECONTEXT->Draw(UINT(vertices.size()), 0);
}
