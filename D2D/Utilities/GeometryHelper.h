#pragma once

class Mesh;

namespace GeometryHelper
{
	shared_ptr<Mesh> CreateRectangle();
	shared_ptr<Mesh> CreateColorCircle(int quality);
}