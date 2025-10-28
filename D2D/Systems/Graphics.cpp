#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	Initialize();
}

Graphics::~Graphics() {}

void Graphics::Initialize()
{

	DXGI_SWAP_CHAIN_DESC desc = { 0 };

    //버퍼 정의
    desc.BufferDesc.Width = 0;
    desc.BufferDesc.Height = 0;

    //수직 동기화 (전체화면 한정) 최대 (분자 / 분모)프레임 으로 제한
    desc.BufferDesc.RefreshRate.Numerator = 60; //분자
    desc.BufferDesc.RefreshRate.Denominator = 1; //분모

    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //버퍼의 RGBA를 각각 8비트씩 보낸다 UNORM = 채널의 값이 0 -> 1
    desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //전체화면 한정
    desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //전체화면 한정

    //샘플 정의 (안티에일리어싱 관련)
    desc.SampleDesc.Count = 1; //Count가 1일땐 반드시 Quality가 0이여야한다. 1이상일때는 Quality도 0이상이여야 한다.
    desc.SampleDesc.Quality = 0;

    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = 1;
    desc.OutputWindow = gHandle;
    desc.Windowed = true; //창모드 여부
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //화면에 렌더하고 그 데이터의 처우
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


    vector<D3D_FEATURE_LEVEL> levels //현재 GPU가 지원을 하는지 확인 (위에서 아래로)
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };
     
    D3D_FEATURE_LEVEL curLevel; //현재 사용중인 레벨
    //대문자 I로 시작하는 클래스(인터페이스)는 직접적인 객체 생성이 불가하고 함수를 이용해 내부에서 객체를 생성해 포인터에 담게한다.
    HRESULT hr = D3D11CreateDeviceAndSwapChain
    (        
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        levels.data(),
        (UINT)levels.size(),
        D3D11_SDK_VERSION,
        &desc,
        &swapChain,
        &device,
        &curLevel,
        &deviceContext
    );
    CHECK(hr);

    CreateBackBuffer(); //백 버퍼 생성


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
        0,
        __uuidof(ID3D11Texture2D), //ID3D11Texture2D 의 ID 값
        (void**)&backBuffer
    );
    CHECK(hr);

    hr = device->CreateRenderTargetView
    (
        backBuffer.Get(),
        nullptr,
        &RTV
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
    deviceContext->OMSetRenderTargets(1, RTV.GetAddressOf(), nullptr); //& 연산은 포인터 주소의 값을 해제하고 반환하기 때문에 GetAddressOf() 사용
    deviceContext->ClearRenderTargetView(RTV.Get(), clearColor);
}

void Graphics::End()
{
    HRESULT hr = swapChain->Present(1 /*수직 동기화 여부*/, 0);
    CHECK(hr);
}
