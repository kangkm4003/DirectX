#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider() : Collider(ColliderType::CIRCLE) {}

	bool IsColliding(Vector2 point) override;
};