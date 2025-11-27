#pragma once

class IndexBuffer
{
public:
	void Create(const vector<UINT>& indicies, D3D11_USAGE usage = D3D11_USAGE_DEFAULT);

	void SetIA();

private:
	ComPtr<ID3D11Buffer> buffer;
	UINT stride = 0;
	UINT offset = 0;
	UINT count = 0;
};