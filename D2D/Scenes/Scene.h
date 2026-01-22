#pragma once
#include <vector>
#include <memory>
#include "Objects/Object.h"

using namespace std;

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void InitScene() = 0; // 생성자() = 0 뜻: 순수 가상 함수 선언
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

	void AddObject(std::shared_ptr<Object> object) //포인터 값 이동으로 복사를 줄여 성능 최적화
	{
		objects.push_back(move(object));
	}

	/*
	std::atmoic<long>
	AddObject(rect);
	*/

private:
	vector<shared_ptr<Object>> objects;
};