#pragma once

class indexBuffer
{
	template<typename T>
	void CreateBuffer(const vector<T>& vertices, D3D11_USAGE usage = D3D11_USAGE_DEFAULT);
	void SetToIA();
private:
	ComPtr<ID3D11Buffer> buffer;
	UINT stride = 0;
	UINT offset = 0;
	UINT count = 0;
};

template<typename T>
inline void indexBuffer::CreateBuffer(const vector<T>& indices, D3D11_USAGE usage)
{
	stride = sizeof(T);
	count = UINT(indices.size());

	D3D11_BUFFER_DESC desc = { 0 };

	desc.ByteWidth = stride * count);
	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	switch (usage)
	{
	case D3D11_USAGE_DEFAULT:
		break;
	case D3D11_USAGE_IMMUTABLE:
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		break;
	}

	D3D11_SUBRESOURCE_DATA subData = { 0 };
	subData.pSysMem = indices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
	CHECK(hr);
}

void indexBuffer::SetToIA()
{
	DEVICECONTEXT->IASetIndexBuffer(buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
