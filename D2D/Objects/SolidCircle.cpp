#include "stdafx.h"
#include "SolidCircle.h"
#include "Renders/Resources/GlobalBuffers.h"
#include "Utilities/GeometryHelper.h"
#include "Systems/ShaderManager.h"

#include "Components/Material.h"
#include "Components/MeshRenderer.h"

SolidCircle::SolidCircle(Vector2 position, Vector2 scale, float rotation, Color color)
	: Object(name, position, scale, rotation)
{
	shared_ptr<Material> marterial = make_shared<Material>(color, 0);
	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();

	meshRenderer->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	meshRenderer->SetMesh(GeometryHelper::CreateSolidColorCircle(50));

	meshRenderer->SetShaderSet(SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));

	AddComponent(marterial);
	AddComponent(meshRenderer);
}

void SolidCircle::Update()
{
	SUPER::Update();
}

void SolidCircle::Render()
{
	SUPER::Render();
}