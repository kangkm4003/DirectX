#include "stdafx.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Components/Transform.h"
#include "Objects/Object.h"

bool BoxCollider::IsColliding(Vector2 point)
{
	const auto& tr = GetOwner()->GetTransform();

	return Collision::Intersect(Collision::RectData(tr->GetPosition(), tr->GetScale()), point);
}

bool BoxCollider::IsColliding(const shared_ptr<Collider>& other)
{
	return other->IsColliding(this);
}

bool BoxCollider::IsColliding(BoxCollider* other)
{
	const auto& myTransform = GetOwner()->GetTransform();
	const auto& otherTransform = other->GetOwner()->GetTransform();

	if (abs(myTransform->GetRotationRadian()) < epsilon && abs(otherTransform->GetRotationRadian()) < epsilon) //만약 각각의 Rect가 회전하지 않았다면 (epsilon 만큼 회전했을때에도)
	{
		return Collision::Intersect(
			Collision::RectData(myTransform->GetPosition(), myTransform->GetScale()),
			Collision::RectData(otherTransform->GetPosition(), otherTransform->GetScale())
			); //AABB 
	}

		return Collision::IntersectOBB(myTransform.get(), otherTransform.get()); //OBB
}

bool BoxCollider::IsColliding(CircleCollider* other)
{
	const auto& myTransform = GetOwner()->GetTransform();
	const auto& otherTransform = other->GetOwner()->GetTransform();

	Vector2 boxPos = myTransform->GetPosition();
	Vector2 boxScale = myTransform->GetScale();
	Vector2 boxHalfSize = Vector2(abs(boxScale.x), abs(boxScale.y)) * 0.5;

	Vector2 circlePos = myTransform->GetPosition();
	Vector2 circleScale = myTransform->GetScale();
	float radius = abs(circlePos.x) * 0.5;

	Vector2 dist = circlePos - boxPos;

	Vector2 boxRightVec = myTransform->GetRight();
	Vector2 boxUpVec = myTransform->GetUp();

	Vector2 dist = circlePos - boxPos;

	Vector2 localCirclePos = Vector2(dist.Dot(myTransform->GetRight()), dist.Dot(myTransform->GetUp()));

	return Collision::Intersect(
		Collision::RectData(boxPos, boxScale),
		Collision::CircleData(localCirclePos, circleScale)
	);
}
