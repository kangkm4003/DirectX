#include "stdafx.h"
#include "Coin.h"

//Components
#include "Components/Collision/CircleCollider.h"
#include "Components/Transform.h"
//

#include "Utilities/Random.h"


Coin::Coin(Vector2 position, Vector2 scale, Color color, UINT segments)
	: CollisionObject(position, scale, 0.f)
{
	AddComponent(make_shared<CircleCollider>("CircleCollider"));

	//Component Precache
	collider = GetComponent<CircleCollider>("CircleCollider");
	transform = GetTransform();
	//
}

void Coin::Update()
{
	SUPER::Update();
}

void Coin::Render()
{
	SUPER::Render();
}

void Coin::onCollision(shared_ptr<Collider> target) //충돌했을 때의 행동
{
	//위치 재설정 (화면 오른쪽 바깥을 기준으로 랜덤한 위치에 스폰)
	transform->SetPosition(Vector2(Random::Range(reSpawnPosMin.x, reSpawnPosMax.x), Random::Range(reSpawnPosMin.y, reSpawnPosMax.y)));
}
