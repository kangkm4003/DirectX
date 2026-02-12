#include "stdafx.h"
#include "CircleCollider.h"
#include "Components/Transform.h"
#include "Objects/Object.h"

bool CircleCollider::IsCollidingWith(ColliderType type, Vector2 position, Vector2 scale)
{
	const auto& tr = GetOwner()->GetTransform();

	//type 인자값에 맞춰 Collision::Intersect 실핼 (CircleCollider 이기에 자신은 무조건 CircleData)
	switch (type)
	{
	case ColliderType::POINT:
	{
		return Collision::Intersect(Collision::CircleData(tr->GetPosition(), tr->GetScale()), position);
	}
	case ColliderType::BOX:
	{
		return Collision::Intersect(Collision::CircleData(tr->GetPosition(), tr->GetScale()), Collision::RectData(position, scale));
	}
	case ColliderType::CIRCLE:
	{
		return Collision::Intersect(Collision::CircleData(tr->GetPosition(), tr->GetScale()), Collision::CircleData(position, scale));
	}
	break;
	}
	return false;
}