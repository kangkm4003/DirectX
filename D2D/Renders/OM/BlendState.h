#pragma once


class BlendState
{
public:
	void Create(const CD3D11_BLEND_DESC& desc);
	void SetOM();
private:
	ComPtr<ID3D11BlendState> blendState;
};