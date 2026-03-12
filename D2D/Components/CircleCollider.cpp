#include "stdafx.h"
#include "CircleCollider.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Objects/Object.h"
#include "Utilities/PhysicsUtils.h"
#include "RigidBody.h"

void CircleCollider::Awake()
{
	auto rb = GetOwner()->GetComponent<RigidBody>("RigidBody");

	if (rb && b2Body_IsValid(rb->GetBodyId()))
	{
		const auto& tr = GetOwner()->GetTransform();
		Vector2 halfScale = tr->GetScale() * 0.5f;

		float radius = PhysicsUtils::PixelsToMeters(max(abs(halfScale.x), abs(halfScale.y)));

		b2Circle circle = { {0.0f, 0.0f}, radius };

		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 1.0f;
		shapeDef.material.friction = 0.5f;
		shapeDef.material.restitution = 0.5f;

		b2CreateCircleShape(rb->GetBodyId(), &shapeDef, &circle);
	}
}

bool CircleCollider::IsColliding(Vector2 point)
{
	const auto& tr = GetOwner()->GetTransform();

	return Collision::Intersect(
		Collision::CircleData(tr->GetPosition(), tr->GetScale()),
		point
	);
}

bool CircleCollider::IsColliding(const shared_ptr<Collider>& other)
{
	if (Collision::Intersect(GetGlobalBounds(), other->GetGlobalBounds()) == false)
		return false;

	return other->IsColliding(this);
}

bool CircleCollider::IsColliding(BoxCollider* other)
{
	return other->IsColliding(this);
}

bool CircleCollider::IsColliding(CircleCollider* other)
{
	const auto& tr = GetOwner()->GetTransform();
	const auto& tr2 = other->GetOwner()->GetTransform();

	return Collision::Intersect(
		Collision::CircleData(tr->GetPosition(), tr->GetScale()),
		Collision::CircleData(tr2->GetPosition(), tr2->GetScale())
	);
}

Collision::RectData CircleCollider::GetGlobalBounds()
{
	const auto& tr = GetOwner()->GetTransform();
	Vector2 scale = tr->GetScale();

	return Collision::RectData(tr->GetPosition(), Vector2(max(scale.x, scale.y)));
}
