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
	transform = GetComponent<Transform>("Transform");
	//
}

void CollisionObject::Update()
{
	SUPER::Update();
}

void CollisionObject::Render()
{
	SUPER::Render();
}

void CollisionObject::addTarget(const string& name, Object* target) //코인이 부딛힐 대상 추가
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
			return;
		}
	}
	std::cout << "Target remove failed, Object name " << name << " is not in target list." << std::endl;
}


