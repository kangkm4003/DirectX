#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider() : Collider(ColliderType::BOX) {}

	bool IsCollidingWith(ColliderType type, Vector2 position, Vector2) override;
	bool IsCollidingWithOBB(shared_ptr<Transform> target); //OBB는 직사각형 형태 끼리에만 유효 하기에 단독 선언
};