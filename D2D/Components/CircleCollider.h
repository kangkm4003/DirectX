#pragma once
#include "Collider.h"

class BoxCollider;
class CircleCollider : public Collider
{
public:
	CircleCollider() : Collider(ColliderType::CIRCLE) {}

	bool IsColliding(Vector2 point) override;

	bool IsColliding(const shared_ptr<Collider>& other) override;

	bool IsColliding(class BoxCollider* other) override;
	bool IsColliding(class CircleCollider* other) override;

	Collision::RectData GetGlobalBounds() override;
};