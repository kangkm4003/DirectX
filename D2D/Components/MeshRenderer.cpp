#include "stdafx.h"
#include "MeshRenderer.h"
#include "Renders/Resources/Mesh.h"

void MeshRenderer::Render()
{
	if (!mesh || !VS || !IL || !PS) return;

	mesh->Render();

	DC->IASetPrimitiveTopology(topology);

	IL->SetIA();
	VS->SetShader();
	PS->SetShader();

	BLEND;

	DC->DrawIndexed(mesh->GetIndexCount(), 0, 0);
}

