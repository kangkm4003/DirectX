#include "stdafx.h"
#include "box2DRect.h"
#include "Components/Transform.h"

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

box2DRect::box2DRect(const b2WorldId& worldId, Vector2 position, Vector2 scale, float rotation, Color color)
	:ColorRect(position, scale, rotation, color)
{
	currState.position = position;
	prevState.position = position;
	currState.angle = XMConvertToRadians(rotation);
	prevState.angle = XMConvertToRadians(rotation);

	//오브젝트의 위치, 기울기
	b2BodyDef BodyDef = b2DefaultBodyDef();
	//BodyDef.type = b2_kinematicBody; //다른물체에겐 물리영향이 가지만 자신은 영향이 없음
	BodyDef.type = b2_dynamicBody; //모든 물리연산이 적용됨 (중력, 충돌, ...)

	BodyDef.rotation = b2MakeRot(this->GetTransform()->GetRotationRadian()); //b2Rot 타입으로 받기 위해 b2MakeRot 함수 이용 
	BodyDef.position = { position.x / Pixel_to_Meter_RATIO, position.y / Pixel_to_Meter_RATIO }; //b2에서는 미터 단위를 쓰기 때문에 픽셀 단위에서 미터 단위로 변환
	BodyDef.angularDamping = 0.5f; //물체끼리 충돌하지 않아도 매 Step 마다 감속할 기울기값 (회전)
	BodyDef.linearDamping = 0.5f; //물체끼리 충돌하지 않아도 매 Step 마다 감속할 속도값
	BodyDef.fixedRotation = false; //물리연산이 되었을때 기울기를 바꿀건지

	boxBodyId = b2CreateBody(worldId, &BodyDef);

	//오브젝트의 형태
	b2Polygon Box = b2MakeBox(scale.x * 0.5 / Pixel_to_Meter_RATIO, scale.y * 0.5 / Pixel_to_Meter_RATIO);
	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;					//밀도(오브젝트의 크기에 따른)
	shapeDef.material.friction = 0.5f;			//마찰력 (매 step 마다 연산)
	shapeDef.material.restitution = 0.3f;		//반발력 (튕겨나감) (충돌 했을때에 속력: 0 ~ 1)

	b2CreatePolygonShape(boxBodyId, &shapeDef, &Box);
}

void box2DRect::Update()
{
	SUPER::Update();
	float dt = DELTA;
	if (dt > 0.25f) dt = 0.25f;

	timeAccumulator += dt;

	while (timeAccumulator >= FIXED_TIME_STEP)
	{
		prevState = currState;

		currState = GetCurrentPhysicsState(boxBodyId);

		timeAccumulator -= FIXED_TIME_STEP;
	}

	float alpha = timeAccumulator / FIXED_TIME_STEP;

	if (b2Body_IsValid(boxBodyId) && this)
	{
		Vector2 renderPos = Vector2::Lerp(prevState.position, currState.position, alpha);
		float renderAngle = lerp(prevState.angle, currState.angle, alpha);

		const auto& boxTr = this->GetTransform();
		boxTr->SetPosition(renderPos);
		boxTr->SetRotationRadian(-renderAngle);
	}
}

void box2DRect::Render()
{
	SUPER::Render();
}
