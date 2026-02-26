#include "stdafx.h"
#include "ColorCircle.h"
#include "Utilities/GeometryHelper.h"
#include "Systems/ShaderManager.h"

#include "Components/Material.h"
#include "Components/MeshRenderer.h"

ColorCircle::ColorCircle(Vector2 position, Vector2 scale, Color color, UINT segments)
	: Object("ColorCircle", position, scale, 0.f)
{
	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();

	meshRenderer->SetMesh(GeometryHelper::CreateColorCircle(segments));

	meshRenderer->SetShaderSet(SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));

	AddComponent(make_shared<Material>(color, 0));
	AddComponent(meshRenderer);
}

void ColorCircle::Update()
{
	SUPER::Update();
}

void ColorCircle::Render()
{
	SUPER::Render();
}