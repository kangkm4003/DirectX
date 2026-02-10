#pragma once
#include "Component.h"
#include "Utilities/Collision.h"

enum class ColliderType { BOX, CIRCLE };

class Collider : public Component
{
public:
	Collider(ColliderType type) : Component("Collider"), type(type) {}
	virtual ~Collider() = default;

	virtual bool IsColliding(Vector2 point) = 0;

	ColliderType GetType() const { return type; }

protected:
	ColliderType type;
};