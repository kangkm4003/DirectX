#include "stdafx.h"
#include "BlendState.h"

void BlendState::Create(const CD3D11_BLEND_DESC& desc)
{
	HRESULT hr = DEVICE->CreateBlendState(&desc, &blendState);
	CHECK(hr);
}

void BlendState::SetOM()
{
	DC->OMSetBlendState(blendState.Get(), nullptr, 0xFFFFFFFF);
}
