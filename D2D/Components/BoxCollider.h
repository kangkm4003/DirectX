#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider() : Collider(ColliderType::BOX) {}

	void Awake() override;

	bool IsColliding(Vector2 point) override;

	bool IsColliding(const shared_ptr<Collider>& other) override;

	bool IsColliding(class BoxCollider* other) override;
	bool IsColliding(class CircleCollider* other) override;

	Collision::RectData GetGlobalBounds() override;
};