#pragma once

struct VertexColor
{
	Vector2 position;
	Color color;
};

class Program
{
public:
	Program();
	~Program();


	void Update();
	void Render();

private:
	vector<VertexColor> vertices;
	ComPtr<ID3D11Buffer> vertexBuffer;

	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3D11InputLayout> inputLayout;
	ComPtr<ID3D11VertexShader> vertexShader;

	ComPtr<ID3DBlob> psBlob;
	ComPtr<ID3D11PixelShader> pixelShader;
};