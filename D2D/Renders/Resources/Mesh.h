#pragma once

class Mesh
{
public:
	void Create(const vector<Vertex>& vertices, const vector<UINT>& indices);
	void Render();


private:
	unique_ptr<VertexBuffer> VB;
	unique_ptr<IndexBuffer> IB;
};