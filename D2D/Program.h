#pragma once

class ColorRect;
class Circle;
class SolidCircle;

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

	unique_ptr<SolidCircle> circle;
};
