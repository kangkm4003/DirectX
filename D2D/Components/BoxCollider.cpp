#include "stdafx.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Components/Transform.h"
#include "Objects/Object.h"

bool BoxCollider::IsCollidingWith(ColliderType type, Vector2 position, Vector2 scale)
{
	const auto& tr = GetOwner()->GetTransform();

	//type 인자값에 맞춰 Collision::Intersect 실핼 (BoxCollider 이기에 자신은 무조건 RectData)
	switch (type)
	{
	case ColliderType::POINT:
	{
		return Collision::Intersect(Collision::RectData(tr->GetPosition(), tr->GetScale()), position);
	}
	case ColliderType::BOX:
	{
		return Collision::Intersect(Collision::RectData(tr->GetPosition(), tr->GetScale()), Collision::RectData(position, scale));
	}
	case ColliderType::CIRCLE:
	{
		return Collision::Intersect(Collision::RectData(tr->GetPosition(), tr->GetScale()), Collision::CircleData(position, scale));
	}
	break;
	}
	// 충돌 하지 않았거나 ColliderType enum에 맞지 않는 값을 입력했다면 false 반환
	return false;
}

bool BoxCollider::IsCollidingWithOBB(shared_ptr<Transform> target)
{
	const auto& tr = GetOwner()->GetTransform();

	return Collision::IntersectOBB(tr, target);
}