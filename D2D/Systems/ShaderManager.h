#pragma once

struct ShaderSet
{
	shared_ptr<class VertexShader> VS;
	shared_ptr<class InputLayout> IL;
	shared_ptr<class PixelShader> PS;
};

class ShaderManager
{
	DECLARE_SINGLETON(ShaderManager)

public:
	ShaderSet GetShader(const wstring& path, const vector<D3D11_INPUT_ELEMENT_DESC>& descs);

private:
	unordered_map<wstring, ShaderSet> shaderCache;
};