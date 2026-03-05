#pragma once
#include "Object.h"

class Transform;
class ObjectGroup : public Object
{
public:
	ObjectGroup(Vector2 position, Vector2 scale = Vector2(1, 1), float rotation = 0.0f, int size = 0);
	~ObjectGroup() override { 
		members.clear();
	}

	//void Add(std::shared_ptr<Object> targetObject, int index = 0, Vector2 groupPosition = Vector2(0, 0)); //가독성을 위해 Add와 Insert로 분리

	virtual void Destroy()
	{
		members.clear();
	}

	virtual void Update()
	{
		SUPER::Update();
		for (const auto& obj : members)
		{
			obj->Update();
		}
	}
	virtual void Render()
	{
		SUPER::Render();
		for (const auto& obj : members)
		{
			obj->Render();
		}
	}


	void Add(shared_ptr<Object> targetObject, Vector2 groupPosition = Vector2(0, 0));

	void Insert(shared_ptr<Object> targetObject, Vector2 groupPosition = Vector2(0, 0), int index = 0);

	//void Remove(string Name); //미완

	vector<shared_ptr<Object>> members;
};