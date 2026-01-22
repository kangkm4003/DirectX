#pragma once
#include "Object.h"

class Line : public Object
{
public:
	Line(Vector2 position, Vector2 scale, float rotation, Color color = RED);

	void Update();
	void Render();
private:
};