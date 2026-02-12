#pragma once
#include "Collider.h"

class CircleCollider;
class BoxCollider : public Collider
{
public:
	BoxCollider() : Collider(ColliderType::BOX) {}

	bool IsColliding(Vector2 point) override;

	bool IsColliding(const shared_ptr<Collider>& other) override;

	bool IsColliding(BoxCollider* other) override;
	bool IsColliding(CircleCollider* other) override;
};