#include "stdafx.h"
#include "ColorCircle.h"
#include "Utilities/GeometryHelper.h"
#include "Systems/ShaderManager.h"

#include "Components/Material.h"
#include "Components/MeshRenderer.h"

ColorCircle::ColorCircle(Vector2 position, Vector2 scale, Color color, UINT segments)
	: Object("ColorCircle", position, scale, 0.f)
{
	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();

	meshRenderer->SetMesh(GeometryHelper::CreateColorCircle(segments));

	meshRenderer->SetShaderSet(SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));

	CD3D11_BLEND_DESC desc(D3D11_DEFAULT);

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; //섞을 비율을 픽셀의 alpha값을 따라가도록
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; //소스 픽셀 alpha의 반전값으로
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = DEVICE->CreateBlendState(&desc, &blendState);
	CHECK(hr);

	AddComponent(make_shared<Material>(color, 0));
	AddComponent(meshRenderer);
}

void ColorCircle::Update()
{
	SUPER::Update();
}

void ColorCircle::Render()
{
	DC->OMSetBlendState(blendState.Get(), nullptr, 0xFFFFFFFF);
	SUPER::Render();
}