#include "stdafx.h"
#include "Physics.h"

namespace
{
	constexpr float FIXED_TIME_STEP = 1.0f / 60.0f;
}

Physics::Physics() {}
Physics::~Physics() {}

void Physics::Init()
{
	if (b2World_IsValid(worldId)) Destroy(); //이미 할당된 월드가 있다면 Destroy하고 다시 할당한다
	
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, -30.0f };
	worldId = b2CreateWorld(&worldDef);

	accumulator = 0;

}

void Physics::Destroy()
{
	if (b2World_IsValid(worldId))
	{
		b2DestroyWorld(worldId);
		worldId = b2_nullWorldId;
	}
}

void Physics::Update()
{
	if (b2World_IsValid(worldId))
	{
		float dt = DELTA;

		if (dt > 0.25f) dt = 0.25f;

		accumulator += dt * timeScale;

		while (accumulator >= FIXED_TIME_STEP)
		{
			b2World_Step(worldId, FIXED_TIME_STEP, subStepCount);

			accumulator -= FIXED_TIME_STEP;
		}
	}
}