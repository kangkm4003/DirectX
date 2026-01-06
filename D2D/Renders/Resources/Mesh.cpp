#include "stdafx.h"
#include "Mesh.h"

void Mesh::Create(const vector<Vertex>& vertices, const vector<UINT>& indices)
{
	VB = make_unique<VertexBuffer>();
	VB->Create(vertices);

	IB = make_unique<IndexBuffer>();
	IB->Create(indices);
}

void Mesh::Render()
{
	if (VB) VB->SetIA();
	if (IB) IB->SetIA();
}