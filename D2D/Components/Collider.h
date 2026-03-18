#pragma once
#include "Component.h"
#include "Utilities/Collision.h"

enum class ColliderType { BOX, CIRCLE };


class Collider : public Component
{
public:
	Collider(ColliderType type, const string& compName) : Component(compName), type(type) {}
	virtual ~Collider() = default;

	virtual bool IsColliding(Vector2 point) = 0;

	virtual bool IsColliding(const shared_ptr<Collider>& other) = 0;

	virtual bool IsColliding(class BoxCollider* other) = 0;
	virtual bool IsColliding(class CircleCollider* other) = 0;

	virtual Collision::RectData GetGlobalBounds() = 0;

	ColliderType GetType() const { return type; }

protected:
	ColliderType type;
};