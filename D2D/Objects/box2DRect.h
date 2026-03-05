#pragma once
#include "ColorRect.h"
#include "Utilities/PhysicsState.h"

class box2DRect : public ColorRect
{
public:
	box2DRect(const b2WorldId& worldId, Vector2 position, Vector2 scale, float rotation, Color color = RED);
	~box2DRect() override = default;

	void Update();
	void Render();

private:
	b2BodyId boxBodyId = b2_nullBodyId;

	float timeAccumulator = 0.0f;

	PhysicsState prevState;
	PhysicsState currState;
};