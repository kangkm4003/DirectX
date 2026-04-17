#include "stdafx.h"

//Components
#include "Components/Collision/CircleCollider.h"
//

#include "Coin.h"

Coin::Coin(Vector2 position, Vector2 scale, Color color, UINT segments)
	: ColorCircle(position, scale, color, segments)
{
	AddComponent(make_unique<CircleCollider>());

	//Component Precache
	collider = GetComponent<CircleCollider>("CircleCollider");
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
