#include "stdafx.h"

#include "Components/Transform.h"

#include "CollisionObject.h"

CollisionObject::CollisionObject(Vector2 position, Vector2 scale, float rotation)
	: Object("CollisionObject", position, scale, rotation)
{

	//Component Precache
	transform = GetTransform();
}

void CollisionObject::Update()
{
	SUPER::Update();

	if (collider == nullptr) return;
	if (transform == nullptr) return;
	if (targets.empty()) return;

	for (const auto& target : targets)
	{
		auto targetCollider = target.second;
		auto targetTransform = targetTransforms[target.first];

		if (targetCollider == nullptr) continue;
		if (targetTransform == nullptr) continue;

		if ((targetTransform->GetPosition() - transform->GetPosition()).LengthSquared() > calculationDistance * calculationDistance)
			continue;

		if (collider->IsColliding(targetCollider))
		{
			onCollision(target.second);
		}
	}
}

void CollisionObject::AddTarget(const string& name, shared_ptr<Collider> target) //부딛힐 대상 추가
{
	for (auto member : targets) //같은 이름을 가진 객체가 이미 존재하는지 검사
	{
		if (member.first == name)
		{
			std::cout << "Target add failed, \"" << name << "\" name is already in use by target list." << std::endl;
			return;
		}
	}
	targets.insert({ name, target });
	targetTransforms.insert({ name, target->GetOwner()->GetTransform() });
}

void CollisionObject::RemoveTarget(const string& name)
{
	for (auto member : targets) //같은 이름을 가진 객체가 이미 존재하는지 검사
	{
		if (member.first == name)
		{
			targets.erase(name);
			targetTransforms.erase(name);
			return;
		}
	}
	std::cout << "Target remove failed, Object name " << name << " is not in target list." << std::endl;
}


