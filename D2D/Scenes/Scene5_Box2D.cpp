#include "stdafx.h"
#include "Scene5_Box2D.h"
#include "Objects/ColorRect.h"
#include "Components/Transform.h"

void Scene5::Init()
{
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.f, -30.f }; //현실 중력 { 0.f, -9.8f}

	worldId = b2CreateWorld(&worldDef);

	{
		auto groundObj = make_shared<ColorRect>(Vector2(CENTER_X, 100), Vector2(800, 20), 0.0f, GREEN);

		auto groundObj_tr = groundObj->GetTransform();

		//오브젝트의 위치, 기울기
		b2BodyDef groundBodyDef = b2DefaultBodyDef();
		groundBodyDef.rotation = b2MakeRot(groundObj_tr->GetRotationRadian()); //b2Rot 타입으로 받기 위해 b2MakeRot 함수 이용 
		groundBodyDef.position = { CENTER_X / Pixel_to_Meter_RATIO, 100.f / Pixel_to_Meter_RATIO }; //b2에서는 미터 단위를 쓰기 때문에 픽셀 단위에서 미터 단위로 변환

		groundBodyId = b2CreateBody(worldId, &groundBodyDef);

		//오브젝트의 형태
		b2Polygon groundBox = b2MakeBox(800 * 0.5 / Pixel_to_Meter_RATIO, 20 * 0.5 / Pixel_to_Meter_RATIO);
		b2ShapeDef shapeDef = b2DefaultShapeDef();

		b2CreatePolygonShape(groundBodyId, &shapeDef, &groundBox);

		AddObject(move(groundObj));
	}

	{
		boxObj = make_shared<ColorRect>(Vector2(CENTER_X, 600), Vector2(50, 50), 0.0f, BLUE);

		//오브젝트의 위치, 기울기
		b2BodyDef BodyDef = b2DefaultBodyDef();
		//BodyDef.type = b2_kinematicBody; //다른물체에겐 물리영향이 가지만 자신은 영향이 없음
		BodyDef.type = b2_dynamicBody; //모든 물리연산이 적용됨

		BodyDef.rotation = b2MakeRot(boxObj->GetTransform()->GetRotationRadian()); //b2Rot 타입으로 받기 위해 b2MakeRot 함수 이용 
		BodyDef.position = { CENTER_X / Pixel_to_Meter_RATIO, 600.f / Pixel_to_Meter_RATIO }; //b2에서는 미터 단위를 쓰기 때문에 픽셀 단위에서 미터 단위로 변환
		BodyDef.angularDamping = 0.5f; //물체끼리 충돌하지 않아도 매 Step 마다 감속할 기울기값 (회전)
		BodyDef.linearDamping = 0.5f; //물체끼리 충돌하지 않아도 매 Step 마다 감속할 속도값
		BodyDef.fixedRotation = false; //물리연산이 되었을때 기울기를 바꿀건지

		boxBodyId = b2CreateBody(worldId, &BodyDef);

		//오브젝트의 형태
		b2Polygon Box = b2MakeBox(50 * 0.5 / Pixel_to_Meter_RATIO, 50 * 0.5 / Pixel_to_Meter_RATIO);
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 1.0f;					//밀도(오브젝트의 크기에 따른)
		shapeDef.material.friction = 0.5f;			//마찰력 (매 step 마다 연산)
		shapeDef.material.restitution = 0.1f;		//반발력 (튕겨나감) (충돌 했을때에 속력: 0 ~ 1)

		b2CreatePolygonShape(boxBodyId, &shapeDef, &Box);

		AddObject(boxObj);
	}
}

void Scene5::Destroy()
{
	if (b2World_IsValid(worldId))
	{
		b2DestroyWorld(worldId);
		worldId = b2_nullWorldId; //object와 유사하게 객체 삭제후 null로 값을 바꿔줘야 한다
	}

	SUPER::Destroy();
}

void Scene5::Update()
{
	if (b2World_IsValid(worldId))
	{
		float scaledDeltaTime = DELTA * timeScale;
		b2World_Step(worldId, scaledDeltaTime, subStepCount);
	}

	if (b2Body_IsValid(boxBodyId) && boxObj)
	{
		b2Vec2 position = b2Body_GetPosition(boxBodyId);
		b2Rot rotation = b2Body_GetRotation(boxBodyId);
		float angle = b2Rot_GetAngle(rotation);

		const auto& boxTransform = boxObj->GetTransform();

		boxTransform->SetPosition(Vector2(position.x, position.y) * Pixel_to_Meter_RATIO);
		boxTransform->SetRotationRadian(-angle);
	}

	SUPER::Update();
}

void Scene5::Render()
{
	SUPER::Render();
}
