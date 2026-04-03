#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	Initialize();
}

Graphics::~Graphics() {}

void Graphics::SetBlendDefault() //Blend State
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


void Graphics::Initialize()
{
	DXGI_SWAP_CHAIN_DESC desc = { 0 };

	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	desc.OutputWindow = gHandle;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = 0;

	vector<D3D_FEATURE_LEVEL> featureLevels
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	D3D_FEATURE_LEVEL currentFeature;

	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featureLevels.data(),
		UINT(featureLevels.size()),
		D3D11_SDK_VERSION,
		&desc,
		&swapChain,
		&device,
		&currentFeature,
		&deviceContext
	);
	CHECK(hr);

	SetBlendDefault();

	CreateBackBuffer();
}

void Graphics::CreateBackBuffer()
{
	HRESULT hr = swapChain->ResizeBuffers
	(
		0,
		UINT(gWinWidth),
		UINT(gWinHeight),
		DXGI_FORMAT_UNKNOWN,
		0
	);
	CHECK(hr);

	ComPtr<ID3D11Texture2D> backBuffer;

	hr = swapChain->GetBuffer
	(
		0, //swapChain 생성시 자동으로 버퍼 생성됨. 몇번째 버퍼에 접근 할건지에 대한 여부
		IID_PPV_ARGS(&backBuffer) //backBuffer 타입에 맞춰 타입 캐스팅 후 backBuffer에 주소값 반환
	);
	CHECK(hr);

	hr = device->CreateRenderTargetView
	(
		backBuffer.Get(),
		nullptr,
		&rtv
	);
	CHECK(hr);

	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = gWinWidth;
	viewport.Height = gWinHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}

void Graphics::Begin()
{
	deviceContext->RSSetViewports(1, &viewport);
	deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf() , nullptr);
	deviceContext->ClearRenderTargetView(rtv.Get(), clearColor);
}

void Graphics::End()
{
	HRESULT hr = swapChain->Present(1, 0);
	CHECK(hr);
}