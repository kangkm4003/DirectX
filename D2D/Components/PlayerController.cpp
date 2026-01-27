#include "stdafx.h"
#include "PlayerController.h"
#include "Transform.h"

void PlayerController::Update()
{
	float dt = DELTA;

	const auto& transform = owner->GetTransform();

	Vector2 direction;

	if (INPUT->Press('W')) direction.y += 1.0f;
	if (INPUT->Press('S')) direction.y -= 1.0f;
	if (INPUT->Press('A')) direction.x -= 1.0f;
	if (INPUT->Press('D')) direction.x += 1.0f;

	if (direction.LengthSquared() > epsilon)
	{
		direction.Normalize();

		transform->Move(direction * speed * dt);
	}

	Vector2 scaleVec = Vector2(speed) * 0.5f * dt;

	if (INPUT->Press(VK_UP))
		transform->AddScale(scaleVec);

	//if (INPUT->Press(VK_DOWN))
	//	transform->AddScale(-scaleVec);
	if (INPUT->Press(VK_DOWN))
	{
		Vector2 currentScale = transform->GetScale();
		Vector2 nextScale = currentScale - scaleVec;
		Vector2::Max(Vector2(1.0f), nextScale, nextScale);
		transform->SetScale(nextScale);
	}

	float rotateAmount = speed * dt;

	if (INPUT->Press(VK_LEFT))
		transform->RotateDegree(-rotateAmount);
	if (INPUT->Press(VK_RIGHT))
		transform->RotateDegree(rotateAmount);
}
