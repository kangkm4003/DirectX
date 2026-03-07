#include "stdafx.h"
#include "SnowCircle.h"
#include "Components/Transform.h"
#include "Utilities/Random.h"

SnowCircle::SnowCircle(Vector2 position, Vector2 scale, Vector2 speedInput, Color color, UINT segments)
	: ColorCircle(position, scale, color, segments)
{
	speed = speedInput;
}

void SnowCircle::Update()
{
	SUPER::Update();

	timeAfterSpawn += DELTA;
	if (myTransform->GetPosition().y > WIN_DEFAULT_HEIGHT || myTransform->GetPosition().y < 0) //눈 이펙트가 화면의 위, 혹은 아래로 사라졌을때 위치 초기화
	{
		if (speed.y <= 0) //객체의 speed.y값이 음수, 혹은 0 일때 (아래로 내려감)
			myTransform->SetPosition(Vector2(WIN_DEFAULT_WIDTH * Random::GetFloat(), WIN_DEFAULT_HEIGHT));
		else if (speed.y > 0) //양수 일때 (위로 올라감)
			myTransform->SetPosition(Vector2(myTransform->GetPosition().x, 0));
	}
	else
		myTransform->Move(Vector2(sinf(timeAfterSpawn * speed.x) * speed.x, speed.y));
}
