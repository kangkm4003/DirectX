#include "stdafx.h"
#include "Coin.h"

//Components
#include "Components/Collision/CircleCollider.h"
//


Coin::Coin(Vector2 position, Vector2 scale, Color color, UINT segments)
	: CollisionObject(position, scale, 0.f)
{
	AddComponent(make_shared<CircleCollider>("CircleCollider"));
	//Component Precache
	collider = GetComponent<CircleCollider>("CircleCollider");
	transform = GetComponent<Transform>("Transform");
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