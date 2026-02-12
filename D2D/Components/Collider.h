#pragma once
#include "Component.h"
#include "Utilities/Collision.h"
#include "Components/Transform.h"

//ToDo: 회전한 직사각형과 원의 충돌 체크 구현하기
enum class ColliderType { POINT, BOX, CIRCLE };

class Collider : public Component
{
public:
	Collider(ColliderType type) : Component("Collider"), type(type) {}
	virtual ~Collider() = default;

	virtual bool IsCollidingWith(ColliderType type, Vector2 position, Vector2 scale) = 0; //충돌 확인할 물체의 형태, 그 물체의 위치와 크기.

	ColliderType GetType() const { return type; }

protected:
	ColliderType type;
};