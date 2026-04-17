#pragma once
#include "Objects/Geometry/ColorCircle.h"

class Coin : ColorCircle
{
public:
	Coin(Vector2 position = Vector2(), Vector2 scale = Vector2(30), Color color = YELLOW, UINT segments = 50);
	~Coin() override = default;

	void Update();
	void Render();

	// 
	float addScore
private:
	shared_ptr<class CircleCollider> collider;
};