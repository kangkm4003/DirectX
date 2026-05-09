#include "stdafx.h"
#include "Jump.h"
#include "Components/Transform.h"

void Jump::Update()
{
	SUPER::Update();
	float dt = DELTA;

	const auto& transform = owner->GetTransform();

	if (onAir)
	{
		transform->Move(Vector2(0.f, speed * DELTA));
		speed -= gravity * DELTA;
	}
}

void Jump::DoJump(float amount)
{
	if (curJumpCount <= maxJumpCount)
	{
		onAir = true;
		speed = amount;
		curJumpCount += 1;
	}
}

void Jump::Land()
{
	speed = 0;
	onAir = false;
	curJumpCount = 1;
}

void Jump::onKeyDown()
{
	SUPER::onKeyDown();
	DoJump(jumpAmount);
}
