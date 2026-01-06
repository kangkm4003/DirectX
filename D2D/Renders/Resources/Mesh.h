#pragma once

class Mesh
{
public:
	void Create(const vector<Vertex>& vertices, const vector<UINT>& indices);
	void Render();

	UINT GetIndexCount() { return IB ? IB->GetCount() : 0; }

private:
	unique_ptr<VertexBuffer> VB;
	unique_ptr<IndexBuffer> IB;
};