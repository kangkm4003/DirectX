#pragma once

class ColorRect
{
public:
	void Create();
	void Update();
	void Render();

	WorldBuffer worldBuffer;
private:
	vector<VertexTexture> vertices;
	VertexBuffer vertexBuffer;

	vector<UINT> indices;
	IndexBuffer indexBuffer;

	InputLayout inputLayout;
	VertexShader vertexShader;
	PixelShader pixelShader;
	
	ComPtr<ID3D11RasterizerState> RS;
	ComPtr<ID3D11ShaderResourceView> SRV;
	ComPtr<ID3D11SamplerState> samplerState;
	ComPtr<ID3D11BlendState> blendState;
};