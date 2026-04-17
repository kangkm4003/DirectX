#pragma once
#include "Objects/Object.h"

class WireCircle : public Object
{
public:
	WireCircle(Vector2 position, Vector2 scale, Color color = RED);

	void Update();
	void Render();
private:
};