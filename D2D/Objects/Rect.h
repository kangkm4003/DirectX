#pragma once

class Rect
{
public:
	Rect(Vector2 position, Vector2 scale, float rotation, Color color = Color(1.f, 0.f, 0.f, 0.f));

	void Update();
	void Render();

private:
	unique_ptr<VertexBuffer> VB;

	unique_ptr<IndexBuffer> IB;

	unique_ptr<VertexShader> VS;

	unique_ptr<InputLayout> IL;

	unique_ptr<PixelShader> PS;

	Vector2 position, scale;
	float rotation = 0.0f;

	Matrix world;
	unique_ptr<WorldBuffer> WB;

	Color color;
};