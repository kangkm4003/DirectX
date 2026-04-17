#pragma once
#include "Objects/Object.h"

class Transform;
class ObjectContainer : public Object
{
public:
	ObjectContainer(Vector2 position, Vector2 scale = Vector2(1, 1), float rotation = 0.0f, int size = 0);
	~ObjectContainer() override {
		members.clear();
	}

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