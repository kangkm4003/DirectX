#pragma once

class Mesh;

namespace GeometryHelper
{
	shared_ptr<Mesh> CreateRectangle();
	shared_ptr<Mesh> CreateColorCircle(UINT quality);
	shared_ptr<Mesh> CreateWireCircle(UINT quality);
	shared_ptr<Mesh> CreateLine();
}