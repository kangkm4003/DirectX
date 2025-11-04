#pragma once

class Graphics
{
	DECLEAR_SINGLETON(Graphics)

public:
	void Initialize();
	void CreateBackBuffer();

	void Begin();
	void End();

	ComPtr<ID3D11Device> GetDivece() const { return device; }
	ComPtr<ID3D11DeviceContext> GetDiveceConText() const { return deviceContext; }

private:
	ComPtr<ID3D11Device> device; //작성하지 않아도 기본적으로  nullptr로 정의된다.
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;
	//IDXGISwapChain* swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> RTV;
	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };
};