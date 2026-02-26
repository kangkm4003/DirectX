#include "stdafx.h"
#include "ColorCircle.h"
#include "SnowCircle.h"
#include "Components/Transform.h"
#include "Utilities/Random.h"

SnowCircle::SnowCircle(Vector2 position, Vector2 scale, Color color, UINT segments)
	: ColorCircle(position, scale, color, segments)
{
	//speed = Random::GetVector2(;
}

void SnowCircle::Update()
{
}

void SnowCircle::Render()
{
}
