#include "stdafx.h"
#include "CircleCollider.h"
#include "Components/Transform.h"
#include "Objects/Object.h"

bool CircleCollider::IsColliding(Vector2 point)
{
	const auto& tr = GetOwner()->GetTransform();

	return Collision::Intersect(
		Collision::CircleData(tr->GetPosition(), tr->GetScale()),
		point
	);
}
