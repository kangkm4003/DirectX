#include "stdafx.h"
#include "Scene6_MousePicking.h"
#include "Objects/box2DRect.h"
#include "Components/Transform.h"
#include "Components/Material.h"
#include "Utilities/Random.h"

namespace
{
	constexpr float FIXED_TIME_STEP = 1.0f / 60.0f;
	constexpr size_t MAX_GHOSTS = 30;

	PhysicsState GetCurrentPhysicsState(b2BodyId bodyId)
	{
		if (!b2Body_IsValid(bodyId)) return { Vector2(), 0.0f };

		b2Vec2 pos = b2Body_GetPosition(bodyId);
		b2Rot rot = b2Body_GetRotation(bodyId);
		float angle = b2Rot_GetAngle(rot);

		return { Vector2(pos.x * Pixel_to_Meter_RATIO, pos.y * Pixel_to_Meter_RATIO), angle };
	}
}

void Scene6::Init()
{
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.f, -30.f }; //현실 중력 { 0.f, -9.8f}

	worldId = b2CreateWorld(&worldDef);

	{
		auto groundObj = make_shared<ColorRect>(Vector2(CENTER_X, 100), Vector2(800, 20), 15.f, GREEN);

		auto groundObj_tr = groundObj->GetTransform();

		//오브젝트의 위치, 기울기
		b2BodyDef groundBodyDef = b2DefaultBodyDef();
		groundBodyDef.rotation = b2MakeRot(-groundObj_tr->GetRotationRadian()); //b2Rot 타입으로 받기 위해 b2MakeRot 함수 이용 
		groundBodyDef.position = { CENTER_X / Pixel_to_Meter_RATIO, 100.f / Pixel_to_Meter_RATIO }; //b2에서는 미터 단위를 쓰기 때문에 픽셀 단위에서 미터 단위로 변환

		groundBodyId = b2CreateBody(worldId, &groundBodyDef);

		//오브젝트의 형태
		b2Polygon groundBox = b2MakeBox(800 * 0.5 / Pixel_to_Meter_RATIO, 20 * 0.5 / Pixel_to_Meter_RATIO);
		b2ShapeDef shapeDef = b2DefaultShapeDef();

		b2CreatePolygonShape(groundBodyId, &shapeDef, &groundBox);

		AddObject(move(groundObj));
	}
}

void Scene6::Destroy()
{
	if (b2World_IsValid(worldId))
	{
		b2DestroyWorld(worldId);
		worldId = b2_nullWorldId; //object와 유사하게 객체 삭제후 null로 값을 바꿔줘야 한다
	}

	SUPER::Destroy();
}

void Scene6::Update()
{
	float dt = DELTA;
	if (dt > 0.25f) dt = 0.25f;

	timeAccumulator += dt;

	while (timeAccumulator >= FIXED_TIME_STEP)
	{

		if (b2World_IsValid(worldId))
		{
			b2World_Step(worldId, FIXED_TIME_STEP, subStepCount);
		}

		timeAccumulator -= FIXED_TIME_STEP;
	}

	if (INPUT->Down(VK_LBUTTON))
	{
		Vector2 mousePos = INPUT->GetMousePos();
		mousePos.y = -mousePos.y + WIN_DEFAULT_HEIGHT;
		auto boxObj = make_shared<box2DRect>(worldId, mousePos, Vector2(50, 50), 0.0f, Random::GetColor());

		
		AddObject(boxObj);
	}

	SUPER::Update();

}

void Scene6::Render()
{
	SUPER::Render();
}