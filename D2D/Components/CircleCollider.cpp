#include "stdafx.h"
#include "CircleCollider.h"
#include "Components/Transform.h"
#include "Objects/Object.h"
#include "BoxCollider.h"

bool CircleCollider::IsColliding(Vector2 point)
{
	const auto& tr = GetOwner()->GetTransform();

	return Collision::Intersect(Collision::CircleData(tr->GetPosition(), tr->GetScale()), point);
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
	//
	float maxScale = max(scale.x, scale.y);

	return Collision::RectData(tr->GetPosition(), Vector2(max(scale.x, scale.y)));
}
