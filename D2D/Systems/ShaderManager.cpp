#include "stdafx.h"
#include "ShaderManager.h"

ShaderManager::ShaderManager() {}
ShaderManager::~ShaderManager() {}

ShaderSet ShaderManager::GetShader(const wstring& path, const vector<D3D11_INPUT_ELEMENT_DESC>& descs)
{
	auto it = shaderCache.find(path);
	if (it != shaderCache.end())
		return it->second;

	ShaderSet newSet;

	newSet.VS = make_shared<VertexShader>();
	newSet.VS->Create(path, "VS");

	newSet.IL = make_shared<InputLayout>();
	newSet.IL->Create(descs, newSet.VS->GetBlob());

	newSet.PS = make_shared<PixelShader>();
	newSet.PS->Create(path, "PS");

	shaderCache.emplace(path, newSet);

	return newSet;
}
