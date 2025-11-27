#pragma once

struct VertexColor
{
	VertexColor() = default;
	VertexColor(const Vector2& position, const Color& color)
		: position(position), color(color) {
	}

	Vector2 position;
	Color color;

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};


struct TextureData
{
	TextureData() = default;
	TextureData(const Vector2& position, const Vector2& uv)
		: position(position), uv(uv) {
	}

	Vector2 position;
	Vector2 uv;

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

struct TransformData
{
	Matrix world;
	Matrix view;
	Matrix projection;
};

struct moveVector
{
	int x = 1;
	int y = 1;
};

class Program
{
public:
	Program();
	~Program();


	void Update();
	void Render();

private:
	moveVector moveVector;
	vector<TextureData> vertices;
	ComPtr<ID3D11Buffer> vertexBuffer;

	vector<UINT> indices;
	ComPtr<ID3D11Buffer> indexBuffer;

	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3D11InputLayout> inputLayout;
	ComPtr<ID3D11VertexShader> vertexShader;

	ComPtr<ID3DBlob> psBlob;
	ComPtr<ID3D11PixelShader> pixelShader;

	Matrix world;
	Matrix view;
	Matrix projection;

	TransformData cpuBuffer;
	ComPtr<ID3D11Buffer> gpuBuffer;

	ComPtr<ID3D11RasterizerState> RS;

	ComPtr<ID3D11ShaderResourceView> SRV;
	ComPtr<ID3D11SamplerState> samplerState;

	ComPtr<ID3D11BlendState> blendState;

	Matrix cS, cR, cT;
};