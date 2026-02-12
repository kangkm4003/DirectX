#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider() : Collider(ColliderType::CIRCLE) {}

	bool IsCollidingWith(ColliderType type, Vector2 position, Vector2) override;
};