#pragma once

#include "stdafx.h"

template <typename T>
class ConstantBuffers
{
public:
	ConstantBuffers()
	{
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(T);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}

	void Update(const T& data)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;

		HRESULT hr = DEVICECONTEXT->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		CHECK(hr);

		memcpy(subResource.pData, &data, sizeof(T));
		DEVICECONTEXT->Unmap(buffer.Get(), 0);
	}

	void SetVS(UINT slot)
	{
		DEVICECONTEXT->VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

	void SetPS(UINT slot)
	{
		DEVICECONTEXT->PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
	}

private:
	ComPtr<ID3D11Buffer> buffer;
};