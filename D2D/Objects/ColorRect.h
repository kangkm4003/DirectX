#pragma once

class ColorRect
{
public:
	ColorRect(Vector2 position, Vector2 scale, float rotation, Color color = RED);

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