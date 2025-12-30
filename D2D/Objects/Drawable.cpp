#include "stdafx.h"
#include "Drawable.h"

Drawable::Drawable(const string& name, Vector2 position, Vector2 scale, float rotation, const wstring& shaderPath)
	: Object(name, position, scale, rotation)
{
	VB = make_unique<VertexBuffer>();

	IB = make_unique<IndexBuffer>();

	VS = make_unique<VertexShader>();
	VS->Create(shaderPath, "VS");

	IL = make_unique<InputLayout>();

	PS = make_unique<PixelShader>();
	PS->Create(shaderPath, "PS");
}

void Drawable::Awake()
{
	SUPER::Awake();
}

void Drawable::Update()
{
	SUPER::Update();
}

void Drawable::Render()
{
	SUPER::Render();

	VB->SetIA();
	IB->SetIA();
	IL->SetIA();

	VS->SetShader();

	PS->SetShader();
}

void Drawable::DrawCall(D3D11_PRIMITIVE_TOPOLOGY topology, bool indexed)
{
	DC->IASetPrimitiveTopology(topology);

	if (indexed)
		DC->DrawIndexed(IB->GetCount(), 0, 0);
	else
		DC->Draw(VB->GetCount(), 0);
}
