#include "stdafx.h"
#include "ColorRect.h"
#include "Components/Graphics/Material.h"
#include "Components/Graphics/MeshRenderer.h"
#include "Utilities/GeometryHelper.h"

ColorRect::ColorRect(Vector2 position, Vector2 scale, float rotation, Color color)
	: Object("ColorRect", position, scale, rotation)
{
	auto renderer = make_shared<MeshRenderer>();

	renderer->SetMesh(GeometryHelper::CreateRectangle());
	renderer->SetShaderSet(SHADERS->GetShader(L"_Shaders/Vertex.hlsl", Vertex::descs));

	AddComponent(make_shared<Material>(color, 0));

	AddComponent(renderer);
}

void ColorRect::Update()
{
	SUPER::Update();
}

void ColorRect::Render()
{
	SUPER::Render();
}