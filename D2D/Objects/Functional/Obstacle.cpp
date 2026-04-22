#include "stdafx.h"
#include "Obstacle.h"

//Components
#include "Components/Collision/BoxCollider.h"
#include "Components/Collision/CircleCollider.h"
#include "Components/Transform.h"

Obstacle::Obstacle(Vector2 position, Vector2 scale, float rotation)
	: CollisionObject(position, scale, rotation)
{
	AddComponent(make_shared<BoxCollider>());
	//Component Precache
	collider = GetComponent<BoxCollider>("BoxCollider");
	transform = GetTransform();
	//
}

void Obstacle::Update()
{
	SUPER::Update();

	if (transform == nullptr) return; //Transform 컴포넌트가 없다면 위치 조정 불가능
	if (scrollSpeed.LengthSquared() < epsilon) return; //scroll 스피드가 0이라면 스크롤 불필요

	transform->SetPosition(transform->GetPosition() + Vector2(scrollSpeed.x * DELTA, scrollSpeed.y * DELTA));
}

void Obstacle::Render()
{
	SUPER::Render();
}

void Obstacle::onCollision(shared_ptr<Collider> target) //충돌했을 때의 행동
{

}