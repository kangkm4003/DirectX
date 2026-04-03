#pragma once

class RasterizerState
{
public:
	void Create();

	void Render();
private:
	ComPtr<ID3D11RasterizerState> RS;
};