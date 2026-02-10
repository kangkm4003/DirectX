#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider() : Collider(ColliderType::BOX) {}

	bool IsColliding(Vector2 point) override;
};