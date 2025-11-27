#pragma once

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void Create(const wstring& path, const string& entryName) = 0;
	virtual void Clear() = 0;
	virtual void SetShader() = 0;

protected:
	void CompileShader(const wstring& path, const string& entryName, const string& profile, ID3DBlob** blob);

	wstring path = L"";
	string entryName = "";


private:
	void CheckShaderError(HRESULT hr, ComPtr<ID3DBlob> error);
};