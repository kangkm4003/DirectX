#include "stdafx.h"
#include "InputLayout.h"

void InputLayout::Create(const vector<D3D11_INPUT_ELEMENT_DESC>& descs, const ComPtr<ID3DBlob>& blob)
{
	assert(!descs.empty() && blob.Get());

	HRESULT hr = DEVICE->CreateInputLayout
	(
		descs.data(),
		UINT(descs.size()),
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&inputLayout
	);
	CHECK(hr);
}

void InputLayout::SetIA()
{

}
