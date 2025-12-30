#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect(Vector2 position, Vector2 scale, float rotation, Color color)
	: position(position), scale(scale), rotation(-XMConvertToRadians(rotation)), color(color)
{
	vector<VertexColor> vertices(4);
	vertices[0].position = { -0.5f, -0.5f };
	vertices[1].position = { -0.5f, 0.5f };
	vertices[2].position = { 0.5f, -0.5f };
	vertices[3].position = { 0.5f, 0.5f };

	for (auto& v : vertices)
		v.color = this->color;

	VB = make_unique<VertexBuffer>();
	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	vector<UINT> indices = { 0, 1, 2, 2, 1, 3 };

	IB = make_unique<IndexBuffer>();
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	VS = make_unique<VertexShader>();
	VS->Create(L"_Shaders/VertexColor.hlsl", "VS");

	IL = make_unique<InputLayout>();
	IL->Create(VertexColor::descs, VS->GetBlob());

	PS = make_unique<PixelShader>();
	PS->Create(L"_Shaders/VertexColor.hlsl", "PS");

	Matrix S = XMMatrixScalingFromVector(this->scale);
	Matrix R = XMMatrixRotationZ(this->rotation);
	Matrix T = XMMatrixTranslationFromVector(this->position);

	world = S * R * T;

	WB = make_unique<WorldBuffer>();
	WB->SetWorld(world);

	WB->Update();
}

void ColorRect::Update()
{

}

void ColorRect::Render()
{
	VB->SetIA();
	IB->SetIA();
	IL->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	VS->SetShader();

	PS->SetShader();

	WB->SetVSBuffer(0);

	DC->DrawIndexed(IB->GetCount(), 0, 0);
}