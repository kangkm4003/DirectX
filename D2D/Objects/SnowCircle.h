#pragma once
#include "ColorCircle.h"

class SnowCircle : public ColorCircle
{
public:
	SnowCircle(Vector2 position, Vector2 scale, Color color = WHITE, UINT segments = 50);
	~SnowCircle() override = default;

	void Update();
	void Render();

private:
	Vector2 speed;
};