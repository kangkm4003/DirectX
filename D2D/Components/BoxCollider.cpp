#include "stdafx.h"
#include "BoxCollider.h"
#include "Components/Transform.h"
#include "Objects/Object.h"

bool BoxCollider::IsColliding(Vector2 point)
{
	const auto& tr = GetOwner()->GetTransform();

	return Collision::Intersect(Collision::RectData(tr->GetPosition(), tr->GetScale()), point);
}
