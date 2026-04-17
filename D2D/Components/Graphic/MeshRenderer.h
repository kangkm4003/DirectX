#pragma once
#include "Components/Component.h"
class Mesh;

class MeshRenderer : public Component
{
public:
	MeshRenderer(const string& name = "MeshRenderer") : Component(name) {}
	~MeshRenderer() override = default;

	void SetMesh(const shared_ptr<Mesh>& mesh) { this->mesh = mesh; }

	void Render();

	void SetShaderSet(const ShaderSet& shaderSet)
	{
		this->VS = shaderSet.VS;
		this->IL = shaderSet.IL;
		this->PS = shaderSet.PS;
	}

	void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) { this->topology = topology; }

private:
	shared_ptr<Mesh> mesh;

	shared_ptr<VertexShader> VS;
	shared_ptr<InputLayout> IL;
	shared_ptr<PixelShader> PS;

	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};