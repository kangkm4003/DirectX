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
	DC->OMSetBlendState(GRAPHICS->GetBlend(), nullptr, 0xFFFFFFFF);

	DC->DrawIndexed(mesh->GetIndexCount(), 0, 0);
}

