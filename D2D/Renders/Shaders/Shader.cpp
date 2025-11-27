#include "stdafx.h"
#include "Shader.h"

void Shader::CompileShader(const wstring& path, const string& entryName, const string& profile, ID3DBlob** blob)
{
	ComPtr<ID3DBlob> error;
	HRESULT hr = D3DCompileFromFile
	(
		path.c_str(),
		nullptr,
		nullptr,
		entryName.c_str(),
		profile.c_str(),
		D3DCOMPILE_ENABLE_STRICTNESS,
		0,
		blob,
		&error
	);
}

void Shader::CheckShaderError(HRESULT hr, ComPtr<ID3DBlob> error)
{

}