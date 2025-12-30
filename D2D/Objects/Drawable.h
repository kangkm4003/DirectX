#pragma once
#include "Object.h"

class Drawable : public Object
{
public:
	Drawable(const string& name, Vector2 position, Vector2 scale, float rotation, const wstring& shaderPath);
	~Drawable() override = default;

	void Awake() override;
	void Update() override;
	void Render() override;

	void DrawCall(D3D11_PRIMITIVE_TOPOLOGY topology, bool indexed = true);

protected:
	unique_ptr<VertexBuffer> VB;
	unique_ptr<IndexBuffer> IB;

	unique_ptr<VertexShader> VS;

	unique_ptr<InputLayout> IL;

	unique_ptr<PixelShader> PS;
};