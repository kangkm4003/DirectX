#pragma once

class ColorRect
{
public:
	void Create();
private:
	vector<VertexTexture> vertices;
	vector<UINT> indices;
	VertexBuffer vertexBuffer;
	VertexShader vertexShader;
	InputLayout inputLayout;
	PixelShader pixelShader;
	WorldBuffer worldBuffer;
	ConstantBuffers<WorldBuffer> constantBuffer;
	ComPtr<ID3D11RasterizerState> RS;
	ComPtr<ID3D11ShaderResourceView> SRV;
	ComPtr<ID3D11SamplerState> samplerState;
	ComPtr<ID3D11BlendState> blendState;
};