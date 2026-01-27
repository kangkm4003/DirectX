#include "stdafx.h"
#include "ColorCircle.h"
#include "Utilities/GeometryHelper.h"
#include "Systems/ShaderManager.h"

#include "Components/Material.h"
#include "Components/MeshRenderer.h"

ColorCircle::ColorCircle(Vector2 position, Vector2 scale, float rotation, Color color)
	: Object(name, position, scale, rotation)
{
	shared_ptr<Material> marterial = make_shared<Material>(color, 0);
	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();

	meshRenderer->SetMesh(GeometryHelper::CreateColorCircle(50));

	meshRenderer->SetShaderSet(SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));

	AddComponent(marterial);
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