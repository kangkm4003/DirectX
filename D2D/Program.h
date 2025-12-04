#pragma once

class Program
{
public:
	Program();
	~Program();

	void SetGlobalBuffers();

	void Update();
	void Render();

private:
	unique_ptr<ViewProjectionBuffer> VPBuffer;

	Matrix view, projection;

	ConstantBuffers< ViewProjectionBuffer> constanBuffer;

	unique_ptr<ColorRect> rect;
};
