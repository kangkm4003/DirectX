#include "stdafx.h"
#include "Jump.h"
#include "Components/Transform.h"

Jump::Jump(float jumpAmount, float gravity, const string& name)
	: KeyMapping(name), jumpAmount(jumpAmount), gravity(gravity)
{
	transform = GetOwner()->GetTransform();
}

void Jump::Update()
{
	SUPER::Update();
	float dt = DELTA;

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

void Jump::Land(shared_ptr<Transform> platform)
{
	speed = 0;
	onAir = false;
	curJumpCount = 1;
	transform->SetPosition(Vector2(
		transform->GetPosition().x,
		platform->GetPosition().y + platform->GetScale().y * 0.5 + transform->GetScale().y * 0.5)); //착지 했을때 바닥에 박히는것을 방지하기 위해 위치 재조정
}

void Jump::onKeyDown()
{
	SUPER::onKeyDown();
	DoJump(jumpAmount);
}
