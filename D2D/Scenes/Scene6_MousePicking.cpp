#include "stdafx.h"
#include "Scene6_MousePicking.h"
#include "Objects/ColorRect.h"
#include "Components/Transform.h"
#include "Utilities/PhysicsUtils.h"
#include "Utilities/Random.h"

namespace
{
	struct PickingContext
	{
		b2Vec2 point;
		b2BodyId hitBodyId;
	};

	bool PickingCallBack(b2ShapeId shapeId, void* context)
	{
		PickingContext* ctx = (PickingContext*)context;

		if (b2Shape_TestPoint(shapeId, ctx->point)) //point가 shape 안에 들어왔는지
		{
			b2BodyId bodyId = b2Shape_GetBody(shapeId);

			if (b2Body_GetType(bodyId) == b2_dynamicBody)
			{
				ctx->hitBodyId = bodyId;
				return false;
			}
		}
	}
}

void Scene6::Init()
{
	CD3D11_RASTERIZER_DESC desc(D3D11_DEFAULT);
	DEVICE->CreateRasterizerState(&desc, &rs);
	desc.FillMode = D3D11_FILL_WIREFRAME;
	DEVICE->CreateRasterizerState(&desc, &wireframe);

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, -30.0f };
	worldId = b2CreateWorld(&worldDef);

	{
		groundObj = make_shared<ColorRect>(Vector2(CENTER_X, 50), Vector2(800, 20), 0.0f, GREEN);
		AddObject(groundObj);

		const auto& tr = groundObj->GetTransform();

		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.position = PhysicsUtils::PixelsToMeters(tr->GetPosition());

		groundBodyId = b2CreateBody(worldId, &bodyDef);

		Vector2 halfScale = tr->GetScale() * 0.5f;
		float hx = PhysicsUtils::PixelsToMeters(halfScale.x);
		float hy = PhysicsUtils::PixelsToMeters(halfScale.y);

		b2Polygon groundBox = b2MakeBox(hx, hy);

		b2ShapeDef shapeDef = b2DefaultShapeDef();

		b2CreatePolygonShape(groundBodyId, &shapeDef, &groundBox);
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
	boxes.clear();
	objects.clear();
}

void Scene6::Update()
{
	if (b2World_IsValid(worldId))
	{
		b2World_Step(worldId, DELTA * timeScale, subStepCount);
	}

	Vector2 mousePixels = Vector2(INPUT->GetMousePos().x, INPUT->GetMousePos().y);
	b2Vec2 mouseMeters = PhysicsUtils::PixelsToMeters(mousePixels);

	if (INPUT->Down(VK_LBUTTON))
	{
		if (b2Joint_IsValid(mouseJointId))
		{
			b2DestroyJoint(mouseJointId);
			mouseJointId = b2_nullJointId;
		}

		float d = 0.001f; //마우스 위치에 아주 작은 임의에 bound를 만든다.
		b2AABB aabb;
		aabb.lowerBound = { mouseMeters.x - d, mouseMeters.y - d };
		aabb.upperBound = { mouseMeters.x + d, mouseMeters.y + d };

		PickingContext context{};
		context.point = mouseMeters;
		context.hitBodyId = b2_nullBodyId;

		b2World_OverlapAABB(worldId, aabb, b2DefaultQueryFilter(), PickingCallBack, &context);

		if (b2Body_IsValid(context.hitBodyId))
		{
			b2MouseJointDef jointDef = b2DefaultMouseJointDef();
			jointDef.bodyIdA = groundBodyId;
			jointDef.bodyIdB = context.hitBodyId;
			jointDef.target = mouseMeters;
			jointDef.maxForce = 1000.f * b2Body_GetMass(context.hitBodyId); //대상의 무게 비례
			jointDef.hertz = 10.f; //높을수록 뻣뻣하며 반응이 빠르다
			jointDef.dampingRatio = 0.7f; //joint의 관성

			mouseJointId = b2CreateMouseJoint(worldId, &jointDef);

			b2Body_SetAwake(context.hitBodyId, true); //물리연산이 없어 수면상태로 전환된 물체를 다시 깨운다
		}
	}

	if (INPUT->Press(VK_LBUTTON) && b2Joint_IsValid(mouseJointId))
	{
		b2MouseJoint_SetTarget(mouseJointId, mouseMeters);

		b2BodyId bodyB = b2Joint_GetBodyB(mouseJointId);
		b2Body_SetAwake(bodyB, true);
	}

	if (INPUT->Up(VK_LBUTTON) && b2Joint_IsValid(mouseJointId)) //만약 물체를 든 상태로 마우스 왼쪽 버튼을 뗀다면 joint 삭제(해제)
	{
		b2DestroyJoint(mouseJointId);
		mouseJointId = b2_nullJointId;
	}

	if (INPUT->Down(VK_RBUTTON))
	{
		CreateBox(mousePixels);
	}

	for (auto& box : boxes)
	{
		if (b2Body_IsValid(box.bodyId))
		{
			b2Vec2 pos = b2Body_GetPosition(box.bodyId);
			b2Rot rot = b2Body_GetRotation(box.bodyId);
			float angle = b2Rot_GetAngle(rot);

			box.visaul->GetTransform()->SetPosition(PhysicsUtils::MetersToPixels(pos));
			box.visaul->GetTransform()->SetRotationRadian(-angle);
		}
	}

	SUPER::Update();
}

void Scene6::Render()
{
	if (INPUT->Press(VK_SPACE))
	{
		DC->RSSetState(wireframe.Get());
	}

	SUPER::Render();

	if (INPUT->Press(VK_SPACE))
	{
		DC->RSSetState(rs.Get());
	}
}

void Scene6::CreateBox(Vector2 screenPos)
{
	auto newRect = make_shared<ColorRect>(screenPos, Vector2(50, 50), 0.f, Random::GetColor());
	AddObject(newRect);

	const auto& tr = newRect->GetTransform();

	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = PhysicsUtils::PixelsToMeters(screenPos);
	bodyDef.angularDamping = 1.0f;
	b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

	Vector2 halfScale = newRect->GetTransform()->GetScale() * 0.5f;
	float hx = PhysicsUtils::PixelsToMeters(halfScale.x);

	b2Polygon box = b2MakeBox(hx, hx);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.material.friction = 0.5f;
	shapeDef.material.restitution = 0.5f;
	b2CreatePolygonShape(bodyId, &shapeDef, &box);

	boxes.push_back({ newRect, bodyId });
}
