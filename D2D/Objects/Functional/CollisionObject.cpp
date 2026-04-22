#include "stdafx.h"

//Components
#include "Components/Collision/Collider.h"
//

#include "CollisionObject.h"

CollisionObject::CollisionObject(Vector2 position, Vector2 scale, float rotation)
	: Object("CollisionObject", position, scale, rotation)
{

	//Component Precache
	collider = GetComponent<Collider>("Collider");
	transform = GetTransform();
	//
}

void CollisionObject::Update()
{
	SUPER::Update();

	if (collider == nullptr) return; //Collider 컴포넌트가 없다면 충돌 검사 불가능
	if (targets.empty()) return; //충돌 대상이 없다면 충돌 검사 불필요

	for (const auto& target : targets)
	{
		if (target.second == nullptr) continue; //충돌 대상이 유효하지 않다면 검사 불필요

		auto targetCollider = target.second;
		if (targetCollider == nullptr) continue; //충돌 대상에 Collider 컴포넌트가 없다면 충돌 검사 불가능

		if (collider->IsColliding(targetCollider))
		{
			onCollision(target.second);
		}
	}
}

void CollisionObject::addTarget(const string& name, shared_ptr<Collider> target) //부딛힐 대상 추가
{
	for (auto member : targets) //같은 이름을 가진 겍체가 이미 존재하는지 검사
	{
		if (member.first == name)
		{
			std::cout << "Target add failed, \"" << name << "\" name is already in use by target list." << std::endl;
			return;
		}
	}
	targets.insert({ name, target });
}

void CollisionObject::removeTarget(const string& name)
{
	for (auto member : targets) //같은 이름을 가진 겍체가 이미 존재하는지 검사
	{
		if (member.first == name)
		{
			targets.erase(name);
			return;
		}
	}
	std::cout << "Target remove failed, Object name " << name << " is not in target list." << std::endl;
}


