#pragma once
#include <vector>
#include <memory>
#include "Objects/Object.h"

using namespace std;

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void InitScene() = 0;
	virtual void Destroy() = 0;

	virtual void Update()
	{
		for (const auto& obj : objects)
		{
			obj->Update();
		}
	}
	virtual void Render()
	{
		for (const auto& obj : objects)
		{
			obj->Render();
		}
	}

	void AddObject(std::shared_ptr<Object> object)
	{
		objects.push_back(object);
	}

private:
	vector<shared_ptr<Object>> objects;
};