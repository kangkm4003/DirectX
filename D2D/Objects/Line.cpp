#include "stdafx.h"
#include "Line.h"
#include "Renders/Resources/GlobalBuffers.h"
#include "Utilities/GeometryHelper.h"
#include "Systems/ShaderManager.h"

#include "Components/Graphic/Material.h"
#include "Components/Graphic/MeshRenderer.h"


Line::Line(Vector2 position, Vector2 scale, float rotation, Color color)
	: Object(name, position, scale, rotation)
{
	shared_ptr<Material> marterial = make_shared<Material>(color, 0);
	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();

	AddComponent(marterial);
	AddComponent(meshRenderer);

	meshRenderer->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	meshRenderer->SetMesh(GeometryHelper::CreateLine());

	ShaderSet setShader = (SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));
	meshRenderer->SetShaderSet(setShader);
}

void Line::Update()
{
	SUPER::Update();
}

void Line::Render()
{
	SUPER::Render();
}