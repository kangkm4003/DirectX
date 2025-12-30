#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect(Vector2 position, Vector2 scale, float rotation, Color color)
	: Drawable("ColorRect", position, scale, rotation, L"_Shaders/VertexColor.hlsl"), color(color)
{
	vector<VertexColor> vertices(4);
	vertices[0].position = { -0.5f, -0.5f };
	vertices[1].position = { -0.5f, 0.5f };
	vertices[2].position = { 0.5f, -0.5f };
	vertices[3].position = { 0.5f, 0.5f };

	for (auto& v : vertices)
		v.color = this->color;

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	vector<UINT> indices = { 0, 1, 2, 2, 1, 3 };

	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexColor::descs, VS->GetBlob());
}

void ColorRect::Update()
{
	SUPER::Update();
}

void ColorRect::Render()
{
	SUPER::Render();

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}