#include "stdafx.h"
#include "RasterizerState.h"

void RasterizerState::Create()
{
	CD3D11_RASTERIZER_DESC desc(D3D11_DEFAULT);

	desc.FillMode = D3D11_FILL_SOLID; //삼각형의 속을 채울지 여부
	desc.CullMode = D3D11_CULL_BACK; //어떤면을 자를지(그리지 않을지) 여부
	desc.FrontCounterClockwise = false; //앞면뒷면 반전

	//HRESULT hr = DEVICE->CreateRasterizerState(&desc, &RS);
	//CHECK(hr);
}

void RasterizerState::Render()
{
	DC->RSSetState(RS.Get());
}
