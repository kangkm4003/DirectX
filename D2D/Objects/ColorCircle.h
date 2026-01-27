#pragma once
#include "Object.h"

class ColorCircle : public Object
{
public:
	ColorCircle(Vector2 position, Vector2 scale, float rotation, Color color = RED);

	void Update();
	void Render();
private:
};