#include "stdafx.h"
#include "BoxCollider.h"
#include "Components/Transform.h"
#include "CircleCollider.h"
#include "Objects/Object.h"

bool BoxCollider::IsColliding(Vector2 point)
{
	const auto& tr = GetOwner()->GetTransform();

	return Collision::Intersect(Collision::RectData(tr->GetPosition(), tr->GetScale()), point);
}

bool BoxCollider::IsColliding(const shared_ptr<Collider>& other)
{
	if (Collision::Intersect(GetGlobalBounds(), other->GetGlobalBounds()) == false)
		return false;

	return other->IsColliding(this);
}

bool BoxCollider::IsColliding(BoxCollider* other)
{
	const auto& myTransform = GetOwner()->GetTransform();
	const auto& otherTransform = other->GetOwner()->GetTransform();

	if (abs(myTransform->GetRotationRadian()) < epsilon && abs(otherTransform->GetRotationRadian()) < epsilon)
	{
		return Collision::Intersect(
			Collision::RectData(myTransform->GetPosition(), myTransform->GetScale()),
			Collision::RectData(otherTransform->GetPosition(), otherTransform->GetScale())
		);
	}

	return Collision::IntersectOBB(myTransform.get(), otherTransform.get());
}

bool BoxCollider::IsColliding(CircleCollider* other)
{
	const auto& myTransform = GetOwner()->GetTransform();
	const auto& otherTransform = other->GetOwner()->GetTransform();

	Vector2 boxPos = myTransform->GetPosition();
	Vector2 boxScale = myTransform->GetScale();
	Vector2 boxHalfSize = Vector2(abs(boxScale.x), abs(boxScale.y)) * 0.5f;

	Vector2 circlePos = otherTransform->GetPosition();
	Vector2 circleScale = otherTransform->GetScale();

	Vector2 dist = circlePos - boxPos;

	Vector2 localCirclePos = Vector2(dist.Dot(myTransform->GetRight()), dist.Dot(myTransform->GetUp()));

	return Collision::Intersect(
		Collision::RectData(boxPos, boxScale),
		Collision::CircleData(localCirclePos + boxPos, circleScale)
	);
}

Collision::RectData BoxCollider::GetGlobalBounds()
{
	const auto& tr = GetOwner()->GetTransform();
	Vector2 scale = tr->GetScale();
	Vector2 right = tr->GetRight();
	Vector2 up = tr->GetUp();

	float w = abs(scale.x);
	float h = abs(scale.y);

	float newHalfWidth = abs(right.x * w) + abs(up.x * h);
	float newHalfHeight = abs(right.y * w) + abs(up.y * h);

	return Collision::RectData(tr->GetPosition(), Vector2(newHalfWidth, newHalfHeight));
}