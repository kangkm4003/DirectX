#pragma once
#include "Object.h"

class ColorRect : public Object
{
public:
	ColorRect(Vector2 position, Vector2 scale, float rotation, Color color = RED);

	void Update();
	void Render();
private:
};