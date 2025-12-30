#pragma once

#include "stdafx.h"

template <typename T>
class ConstantBuffer
{
public:
	void Update()
	{
		D3D11_MAPPED_SUBRESOURCE subResource;

		HRESULT hr = DC->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		CHECK(hr);

		memcpy(subResource.pData, &data, sizeof(T));

		DC->Unmap(buffer.Get(), 0);
	}

	void SetVSBuffer(UINT slot)
	{
		DC->VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

	void SetPSBuffer(UINT slot)
	{
		DC->PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

	virtual ~ConstantBuffer() = default;

protected:
	ConstantBuffer()
	{
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = (sizeof(T) + 15) & ~15;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}

	T data;

private:
	ComPtr<ID3D11Buffer> buffer;
};