#include "stdafx.h"
#include "Program.h"



Program::Program()
{
	// vertexData (삼각형모양으로 픽셀 지정하기)
	{
		vertices.assign(4, TextureData());
		vertices[0].position = { -0.5f, -0.5f };
		vertices[0].uv = { 0.0f, 1.0f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[1].uv = { 0.0f, 0.0f };
		vertices[2].position = { 0.5f, -0.5f };
		vertices[2].uv = { 1.0f, 1.0f };
		vertices[3].position = { 0.5f, 0.5f };
		vertices[3].uv = { 1.0f, 0.0f };
	}
	/*for (auto& vertex : vertices)
	{
		vertex.color = { 1.0f, 0.0f, 0.0f, 1.0f };
	}*/

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

	// indexData
	{
		indices = { 0, 1, 2, 2, 1, 3 };
	}

	// indexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };

		desc.ByteWidth = sizeof(indices[0]) * UINT(indices.size());
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subData = { 0 };
		subData.pSysMem = indices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &indexBuffer);
		CHECK(hr);
	}

	// vsBlob
	{
		HRESULT hr = D3DCompileFromFile
		(
			L"_Shaders/Texture.hlsl",
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
			L"_Shaders/Texture.hlsl",
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

	//Local Position to World position
	{
		Matrix S, R, T;

		S._11 = 300.f; //스케일 X 
		S._22 = 200.f; //스케일 Y

		constexpr float angle = XMConvertToRadians(0); //기울기 (각도에서 라디안 값으로)
		R._11 = cosf(angle);
		R._12 = sinf(angle);
		R._21 = -sinf(angle);
		R._22 = cosf(angle);

		T._41 = 0.f; //월드상 위치값
		T._42 = 0.f;

		cS = S;
		cR = R;
		cT = T;

		cpuBuffer.world = S * R * T; //오브젝트의 월드상에 크기, 위치, 기울기 값

		cpuBuffer.view = XMMatrixLookAtLH(Vector3(0,0,0), Vector3(0, 0, 1), Vector3(0, 1, 0)); //카메라가 바라보는 위치, 방향, 위쪽 방향

		cpuBuffer.projection = XMMatrixOrthographicLH(gWinWidth, gWinHeight, 0, 1);
	}

	// constant buffer 
	{ 
		D3D11_BUFFER_DESC desc = { 0 };

		desc.ByteWidth = sizeof(cpuBuffer);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		
		D3D11_SUBRESOURCE_DATA subData = { 0 };
		subData.pSysMem = &cpuBuffer;

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &gpuBuffer);
		CHECK(hr);
	}

	//RasterizerState
	{
		CD3D11_RASTERIZER_DESC desc(D3D11_DEFAULT);

		desc.FillMode = D3D11_FILL_SOLID; //삼각형의 속을 채울지 여부
		desc.CullMode = D3D11_CULL_BACK; //어떤면을 자를지 여부
		desc.FrontCounterClockwise = FALSE; //앞면뒷면 반전

		HRESULT hr = DEVICE->CreateRasterizerState(&desc, &RS);
		CHECK(hr);
	}

	//Shader Resourece View
	{
		wstring path = L"_Textures/Tree.png";

		ScratchImage image;

		HRESULT hr = LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);
		CHECK(hr);

		hr = CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), &SRV);
		CHECK(hr);
	}

	//Sampler State
	{
		CD3D11_SAMPLER_DESC desc(D3D11_DEFAULT);

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; //픽셀의 색상값을 평균을 내서(보간)출력할건지에 대한 여부
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP; //만약 이미지의 크기 너머의 uv 색상을 가져오려 할경우
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		desc.BorderColor[0] = 1.0f;
		desc.BorderColor[1] = 1.0f;
		desc.BorderColor[2] = 1.0f;
		desc.BorderColor[3] = 1.0f;

		HRESULT hr = DEVICE->CreateSamplerState(&desc, &samplerState);
		CHECK(hr);
	}

	//Blend State
	{
		CD3D11_BLEND_DESC desc(D3D11_DEFAULT);

		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; //섞을 비율을 픽셀의 alpha값을 따라가도록
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; //소스 픽셀 alpha의 반전값으로
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HRESULT hr = DEVICE->CreateBlendState(&desc, &blendState);
		CHECK(hr);
	}
}

Program::~Program()
{
	
}

void Program::Update()
{
	float moveSpeed = 200.0f * DELTA;

	cS *= XMMatrixScaling(1, 1, 0);
	cR *= XMMatrixRotationZ(0.03f);
	if (cT._41 >= WIN_DEFAULT_WIDTH / 2 || cT._41 <= -WIN_DEFAULT_WIDTH / 2)
		moveVector.x = moveVector.x * -1;
	if (cT._42 >= WIN_DEFAULT_HEIGHT / 2 || cT._42 <= -WIN_DEFAULT_HEIGHT / 2)
		moveVector.y = moveVector.y * -1;

	cT *= XMMatrixTranslation(moveSpeed * moveVector.x, moveSpeed * moveVector.y, 0);
	cpuBuffer.world = cS * cR * cT;

	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	DEVICECONTEXT->Map
	(
		gpuBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedSubResource
	);
	memcpy(mappedSubResource.pData, &cpuBuffer, sizeof(cpuBuffer));
	DEVICECONTEXT->Unmap(gpuBuffer.Get(), 0);
}

void Program::Render()
{
	UINT stride = sizeof(vertices[0]);
	UINT offset = 0;

	//IA
	DEVICECONTEXT->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	DEVICECONTEXT->IASetInputLayout(inputLayout.Get());
	DEVICECONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//cBuffer
	DEVICECONTEXT->VSSetConstantBuffers(0, 1, gpuBuffer.GetAddressOf());

	//VS
	DEVICECONTEXT->VSSetShader(vertexShader.Get(), nullptr, 0);

	//RS
	DEVICECONTEXT->RSSetState(RS.Get());

	//PS
	DEVICECONTEXT->PSSetShader(pixelShader.Get(), nullptr, 0);
	DEVICECONTEXT->PSSetShaderResources(0, 1, SRV.GetAddressOf());
	DEVICECONTEXT->PSSetSamplers(0, 1, samplerState.GetAddressOf());

	//OM
	DEVICECONTEXT->OMSetBlendState(blendState.Get(), nullptr, 0xFFFFFFFF);


	//DEVICECONTEXT->Draw(UINT(vertices.size()), 0);
	DEVICECONTEXT->DrawIndexed(UINT(indices.size()), 0, 0);
}
