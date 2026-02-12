#include "stdafx.h"
#include "CircleCollider.h"
#include "Components/Transform.h"
#include "Objects/Object.h"
#include "BoxCollider.h"

bool CircleCollider::IsColliding(Vector2 point)
{
	const auto& tr = GetOwner()->GetTransform();

	return Collision::Intersect(Collision::RectData(tr->GetPosition(), tr->GetScale()), point);
}

bool CircleCollider::IsColliding(const shared_ptr<Collider>& other)
{
	return other->IsColliding(this);
}

bool CircleCollider::IsColliding(BoxCollider* other)
{
	return other->IsColliding(this);
}

bool CircleCollider::IsColliding(CircleCollider* other)
{
	const auto& myTransform = GetOwner()->GetTransform();
	const auto& otherTransform = other->GetOwner()->GetTransform();

	return Collision::Intersect(
		Collision::CircleData(myTransform->GetPosition(), myTransform->GetScale()),
		Collision::CircleData(otherTransform->GetPosition(), otherTransform->GetScale())
	);
}
