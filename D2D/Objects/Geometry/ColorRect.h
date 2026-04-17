#pragma once
#include "Objects/Object.h"

class ColorRect : public Object
{
public:
	ColorRect(Vector2 position, Vector2 scale, float rotation, Color color = RED);
	~ColorRect() override = default;

	void Update();
	void Render();
};