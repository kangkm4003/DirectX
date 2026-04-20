#pragma once
#include <vector>
#include <memory>
#include "Objects/Object.h"

using namespace std;

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Init() = 0; // ������() = 0 ��: ���� ���� �Լ� ����
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

	void AddObject(std::shared_ptr<Object> object) //������ �� �̵����� ���縦 �ٿ� ���� ����ȭ
	{
		objects.push_back(move(object));
	}

	/*
	std::atmoic<long>
	AddObject(rect);
	*/

protected:
	vector<shared_ptr<Object>> objects;
};