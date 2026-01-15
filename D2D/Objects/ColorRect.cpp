#include "stdafx.h"
#include "ColorRect.h"
#include "Renders/Resources/GlobalBuffers.h"
#include "Utilities/GeometryHelper.h"
#include "Systems/ShaderManager.h"

#include "Components/Material.h"
#include "Components/MeshRenderer.h"


ColorRect::ColorRect(Vector2 position, Vector2 scale, float rotation, Color color)
	: Object(name, position, scale, rotation)
{
	shared_ptr<Material> marterial = make_shared<Material>(color, 0);
	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();

	AddComponent(marterial);
	AddComponent(meshRenderer);

	meshRenderer->SetMesh(GeometryHelper::CreateRectangle());

	ShaderSet setShader = (SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));
	meshRenderer->SetShaderSet(setShader);
}

void ColorRect::Update()
{
	SUPER::Update();
}

void ColorRect::Render()
{
	SUPER::Render();
}