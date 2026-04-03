#pragma once

class Graphics
{
	DECLARE_SINGLETON(Graphics)

public:
	void Initialize();
	void CreateBackBuffer();

	void Begin();
	void End();
	
public:
	ID3D11Device* GetDevice() const { return device.Get(); }
	ID3D11DeviceContext* GetDC() const { return deviceContext.Get(); }
	ID3D11BlendState* GetBlend() const { return blendState.Get(); }
	void SetBlendDefault();

private:
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11RenderTargetView> rtv;

	ComPtr<ID3D11BlendState> blendState;


	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };
};