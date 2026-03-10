#include "stdafx.h"
#include "Scene5_Box2D.h"
#include "Objects/ColorRect.h"
#include "Components/Transform.h"
#include "Components/Material.h"
#include "Utilities/Random.h"
#include "Utilities/PhysicsUtils.h"

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

		return { PhysicsUtils::MetersToPixels(pos), angle};
	}
}

void Scene5::Init()
{
	CD3D11_RASTERIZER_DESC desc(D3D11_DEFAULT);

	DEVICE->CreateRasterizerState(&desc, &rs);

	desc.FillMode = D3D11_FILL_WIREFRAME;
	DEVICE->CreateRasterizerState(&desc, &wireframe);

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

	{
		boxObj = make_shared<ColorRect>(Vector2(CENTER_X, 600), Vector2(50, 50), 0.0f, BLUE);

		//오브젝트의 위치, 기울기
		b2BodyDef BodyDef = b2DefaultBodyDef();
		//BodyDef.type = b2_kinematicBody; //다른물체에겐 물리영향이 가지만 자신은 영향이 없음
		BodyDef.type = b2_dynamicBody; //모든 물리연산이 적용됨 (중력, 충돌, ...)

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
		shapeDef.material.restitution = 0.3f;		//반발력 (튕겨나감) (충돌 했을때에 속력: 0 ~ 1)

		b2CreatePolygonShape(boxBodyId, &shapeDef, &Box);

		AddObject(boxObj);
	}

	currState = GetCurrentPhysicsState(boxBodyId);
	prevState = currState;
	timeAccumulator = 0.0f;
}

void Scene5::Destroy()
{
	if (b2World_IsValid(worldId))
	{
		b2DestroyWorld(worldId);
		worldId = b2_nullWorldId; //object와 유사하게 객체 삭제후 null로 값을 바꿔줘야 한다
	}

	SUPER::Destroy();
	ghostTrails.clear();
}

void Scene5::Update()
{
	float dt = DELTA;
	if (dt > 0.25f) dt = 0.25f;

	timeAccumulator += dt;

	while (timeAccumulator >= FIXED_TIME_STEP)
	{
		prevState = currState;

		if (b2World_IsValid(worldId))
		{
			b2World_Step(worldId, FIXED_TIME_STEP, subStepCount);
		}

		currState = GetCurrentPhysicsState(boxBodyId);

		timeAccumulator -= FIXED_TIME_STEP;
	}

	float alpha = timeAccumulator / FIXED_TIME_STEP;

	if (b2Body_IsValid(boxBodyId) && boxObj)
	{
		Vector2 renderPos = Vector2::Lerp(prevState.position, currState.position, alpha);
		float renderAngle = lerp(prevState.angle, currState.angle, alpha);

		const auto& boxTr = boxObj->GetTransform();
		boxTr->SetPosition(renderPos);
		boxTr->SetRotationRadian(-renderAngle);

		float distSq = Vector2::DistanceSquared(renderPos, lastRecordedPos); //잔상끼리의 거리 (일정 거리를 이동했을때 마다 잔상을 생성)

		if (distSq > 100.0f)
		{
			GhostData data = { renderPos, renderAngle };
			ghostTrails.push_back(data);
			lastRecordedPos = renderPos;

		}
		if (ghostTrails.size() > MAX_GHOSTS) ghostTrails.pop_front();
	}

	SUPER::Update();
}

void Scene5::Render()
{
	SUPER::Render();

	if (boxObj) //isVaild
	{
		const auto& tr = boxObj->GetTransform();
		
		const Vector2 originalPos = tr->GetPosition();
		const float originalAngle = tr->GetRotationRadian();

		DC->RSSetState(wireframe.Get());
		for (const auto& ghost : ghostTrails)
		{
			tr->SetPosition(ghost.position);
			tr->SetRotationRadian(-ghost.angle);
			boxObj->GetComponent<Material>("Material")->SetColor(Random::GetColor());
			tr->Update();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
			boxObj->Render();
		}
		DC->RSSetState(rs.Get());

		tr->SetPosition(originalPos);
		tr->SetRotationRadian(-originalAngle);
		boxObj->GetComponent<Material>("Material")->SetColor(BLUE);
		tr->Update();
	}
}