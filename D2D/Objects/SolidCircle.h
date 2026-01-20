#pragma once
#include "Object.h"

class SolidCircle : public Object
{
public:
	SolidCircle(Vector2 position, Vector2 scale, float rotation, Color color = RED);

	void Update();
	void Render();
private:
};