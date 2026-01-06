#pragma once
#include "Drawable.h"

class ColorRect : public Drawable
{
public:
	ColorRect(Vector2 position, Vector2 scale, float rotation, Color color = RED);

	void Update();
	void Render();

private:
	//Color color;
	unique_ptr<class ColorBuffer> CB;
};