#include "stdafx.h"
#include "ColorRect.h"

void ColorRect::Create()
{
	// vertexData (삼각형모양으로 픽셀 지정하기)
	{
		vertices.assign(4, VertexTexture());
		vertices[0].position = { -0.5f, -0.5f };
		vertices[0].uv = { 0.0f, 1.0f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[1].uv = { 0.0f, 0.0f };
		vertices[2].position = { 0.5f, -0.5f };
		vertices[2].uv = { 1.0f, 1.0f };
		vertices[3].position = { 0.5f, 0.5f };
		vertices[3].uv = { 1.0f, 0.0f };
	}

	// vertexBuffer
	{
		vertexBuffer.Create(vertices, D3D11_USAGE_IMMUTABLE);
	}

	// indexData
	{
		indices = { 0, 1, 2, 2, 1, 3 };
	}

	// indexBuffer
	{
		indexBuffer.Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	// vertexShader
	{
		vertexShader.Create(L"_Shaders/VertexTexture.hlsl", "VS");
	}

	// pixelShader
	{
		pixelShader.Create(L"_Shaders/VertexTexture.hlsl", "PS");
	}

	// inputLayoutDesc
	{
		inputLayout.Create(VertexTexture::descs, vertexShader.GetBlob());
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

		T._41 = 0.0f; //월드상 위치값
		T._42 = 0.0f;

		worldBuffer.SetWorld(S * R * T);
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

		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &SRV);
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

void ColorRect::Update()
{

}

void ColorRect::Render()
{
	// IA
	vertexBuffer.SetIA();
	indexBuffer.SetIA();
	worldBuffer.SetVSBuffer(0);
	inputLayout.SetIA();
	DEVICECONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// VS
	vertexShader.SetShader();

	// RS
	DEVICECONTEXT->RSSetState(RS.Get());

	// PS
	pixelShader.SetShader();
	DEVICECONTEXT->PSSetShaderResources(0, 1, SRV.GetAddressOf());
	DEVICECONTEXT->PSSetSamplers(0, 1, samplerState.GetAddressOf());

	// OM
	DEVICECONTEXT->OMSetBlendState(blendState.Get(), nullptr, 0xFFFFFFFF);

	DEVICECONTEXT->DrawIndexed(UINT(indices.size()), 0, 0);
}