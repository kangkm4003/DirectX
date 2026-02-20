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
	if (Collision::Intersect(GetGlobalBounds(), other->GetGlobalBounds()) == false) //가상의 경계선에 들어와 있지 않다면 연산없이 바로 false 반환
		return false;

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

	//로컬 기준 수직, 수평 길이
	float width = abs(scale.x) * 0.5f;
	float height = abs(scale.y) * 0.5f;

	//right와 up 백터를 참조해 대상의 회전하지 않은 가상 경계선 사각형을 구한다
	float newHalfWidth = abs(right.x * width) + abs(up.x * height);
	float newHalfHeight = abs(right.y * width) + abs(up.y * height);


	return Collision::RectData(tr->GetPosition(), Vector2(newHalfWidth, newHalfHeight) * 2.f);
}
