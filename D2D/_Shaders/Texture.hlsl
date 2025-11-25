struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCORD0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
    float2 uv : TEXCORD0;
};

cbuffer TransformBuffer : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _projection;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
	
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    output.uv = input.uv;
	
    return output;
}

Texture2D sourceTex : register(t0);

SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_Target0
{
    float4 color = sourceTex.Sample(samp, input.uv);
	
    return color;
}