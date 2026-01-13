#pragma once
#include "Object.h"

class Circle : public Object
{
public:
	Circle(Vector2 position, Vector2 scale, float rotation, Color color = RED);

	void Update();
	void Render();
private:
};