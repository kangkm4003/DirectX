#include "stdafx.h"
#include "ColorRect.h"

void ColorRect::Create()
{
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

	indices = { 0, 1, 2, 2, 1, 3 };

	{
		Matrix S, R, T;

		S._11 = 300.f; //스케일 X 
		S._22 = 200.f; //스케일 Y

		constexpr float angle = XMConvertToRadians(-90); //기울기 (각도에서 라디안 값으로)
		R._11 = cosf(angle);
		R._12 = sinf(angle);
		R._21 = -sinf(angle);
		R._22 = cosf(angle);

		T._41 = 0.f; //월드상 위치값
		T._42 = 0.f;

		worldBuffer.SetWorld(S * R * T); //오브젝트의 월드상에 크기, 위치, 기울기 값
	}
	
	vertexBuffer.Create(vertices);
	vertexShader.Create(L"_Shaders / Texture.hlsl", "VS");
	inputLayout.Create(VertexTexture::descs, vertexShader.GetBlob());
	pixelShader.Create(L"_Shaders / Texture.hlsl", "PS");

	{
		CD3D11_RASTERIZER_DESC desc(D3D11_DEFAULT);

		desc.FillMode = D3D11_FILL_SOLID; //삼각형의 속을 채울지 여부
		desc.CullMode = D3D11_CULL_BACK; //어떤면을 자를지 여부
		desc.FrontCounterClockwise = FALSE; //앞면뒷면 반전

		HRESULT hr = DEVICE->CreateRasterizerState(&desc, &RS);
		CHECK(hr);
	}

	{
		wstring path = L"_Textures/bk.bmp";

		ScratchImage image;

		HRESULT hr = LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);
		CHECK(hr);

		hr = CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), &SRV);
		CHECK(hr);
	}
}