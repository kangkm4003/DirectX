#include "stdafx.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Utilities/PhysicsUtils.h"

RigidBody::RigidBody(BodyType type, const string& name)
	: Component(name)
{
	bodyDef = b2DefaultBodyDef();
	bodyDef.type = (b2BodyType)type;
}

RigidBody::~RigidBody()
{
	if (b2World_IsValid(PHYSICS->GetWorldId())) //worldId와 bodyId가 유효할때 Destroy 호출
		if (b2Body_IsValid(bodyId)) b2DestroyBody(bodyId);
}

void RigidBody::Awake()
{
	auto tr = GetOwner()->GetTransform();

	bodyDef.position = PhysicsUtils::PixelsToMeters(tr->GetPosition());
	bodyDef.rotation = b2MakeRot(-tr->GetRotationRadian());

	bodyDef.userData = GetOwner(); //

	auto worldId = PHYSICS->GetWorldId();
	if (b2World_IsValid(worldId))
	{
		if (b2World_IsValid(worldId))
			bodyId = b2CreateBody(worldId, &bodyDef);
	}
}

void RigidBody::Update()
{
	if (bodyDef.type == b2_staticBody || !b2Body_IsValid(bodyId)) return; //tyoe이 static이거나 객체가 유효하지 않을땐 함수실행 중지

	b2Vec2 pos = b2Body_GetPosition(bodyId);
	b2Rot rot = b2Body_GetRotation(bodyId);
	float angle = b2Rot_GetAngle(rot);

	const auto& tr = GetOwner()->GetTransform();
	tr->SetPosition(PhysicsUtils::MetersToPixels(pos));
	tr->SetRotationRadian(-angle);
}

void RigidBody::SetPosition(Vector2 position)
{
	GetOwner()->GetTransform()->SetPosition(position);
	if (b2Body_IsValid(bodyId)) //객체가 유효할때
	{
		b2Vec2 pos = PhysicsUtils::PixelsToMeters(position);
		b2Rot rot = b2Body_GetRotation(bodyId);
		b2Body_SetTransform(bodyId, pos, rot);
		b2Body_SetAwake(bodyId, true);
	}
}

void RigidBody::SetRotationRadian(float radian)
{
	GetOwner()->GetTransform()->SetRotationRadian(radian);

	if (b2Body_IsValid(bodyId))
	{
		b2Vec2 pos = b2Body_GetPosition(bodyId);
		b2Body_SetTransform(bodyId, pos, b2MakeRot(-radian));
		b2Body_SetAngularVelocity(bodyId, 0.f);
		b2Body_SetAwake(bodyId, true);
	}
}

void RigidBody::SetRotationDegree(float degree)
{
	float radian = XMConvertToRadians(degree);
	GetOwner()->GetTransform()->SetRotationRadian(radian);

	if (b2Body_IsValid(bodyId))
	{
		b2Vec2 pos = b2Body_GetPosition(bodyId);
		b2Body_SetTransform(bodyId, pos, b2MakeRot(-radian));
		b2Body_SetAngularVelocity(bodyId, 0.f);
		b2Body_SetAwake(bodyId, true);
	}
}

void RigidBody::SetVelocity(Vector2 velocity)
{
	auto velocityMeters = PhysicsUtils::PixelsToMeters(velocity);

	bodyDef.linearVelocity = velocityMeters;

	if (b2Body_IsValid(bodyId))
	{
		b2Body_SetLinearVelocity(bodyId, velocityMeters); // 초당 이동할 거리 (미터)
	}
}

void RigidBody::SetDamping(float linear, float angular)
{
	bodyDef.linearDamping = linear;
	bodyDef.angularDamping = angular;

	if (b2Body_IsValid(bodyId))
	{
		b2Body_SetLinearDamping(bodyId, linear);
		b2Body_SetAngularDamping(bodyId, angular);
	}

}

void RigidBody::SetFixedRotation(bool fixed)
{
	bodyDef.fixedRotation = fixed;
	if (b2Body_IsValid(bodyId)) b2Body_SetFixedRotation(bodyId, fixed);
}