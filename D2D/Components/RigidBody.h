#pragma once
#include "Component.h"

enum class BodyType { 
	Static = b2_staticBody, 
	Dynamic = b2_dynamicBody, 
	Kinematic = b2_kinematicBody 
};

class RigidBody : public Component
{
public:
	RigidBody(BodyType type = BodyType::Dynamic, const string& name = "RigidBody");
	~RigidBody() override;

	void Awake() override;
	void Update() override;

	void SetPosition(Vector2 position);
	void SetRotationDegree(float degree);
	void SetRotationRadian(float radian);

	void SetVelocity(Vector2 velocity);
	void SetDamping(float linear, float angular);
	void SetFixedRotation(bool fixed);

	b2BodyId GetBodyId() const { return bodyId; }
private:
	b2BodyId bodyId = b2_nullBodyId;
	b2BodyDef bodyDef;
};