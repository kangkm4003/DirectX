#pragma once
#include <vector>
#include <memory>
#include "Objects/Object.h"

using namespace std;

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Init() = 0; // 생성자() = 0 뜻: 순수 가상 함수 선언
	virtual void Destroy()
	{
		objects.clear();
	}

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

	void AddObject(std::shared_ptr<Object> object) //포인터 값 이동으로 복사를 줄여 성능 최적화
	{
		object->Awake();
		objects.push_back(move(object));
	}

	/*
	std::atmoic<long>
	AddObject(rect);
	*/

protected:
	vector<shared_ptr<Object>> objects;
};