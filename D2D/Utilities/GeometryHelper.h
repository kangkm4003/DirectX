#pragma once

// ToDo : 원과 속이 빈 원그리기
class Mesh;

namespace GeometryHelper
{
	shared_ptr<Mesh> CreateRectangle();
	shared_ptr<Mesh> CreateColorCircle(UINT quality);
	shared_ptr<Mesh> CreateSolidColorCircle(UINT quality);
}