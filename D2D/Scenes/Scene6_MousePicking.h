#pragma once
#include "Scene.h"
#include "Utilities/PhysicsState.h"
#include <deque>

class ObjectGroup;

class Scene6 : public Scene
{
public:
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;

private:
	b2WorldId worldId = b2_nullWorldId;

	b2BodyId groundBodyId = b2_nullBodyId;

	float timeScale = 1.f; //시간이 흘러가는 배율
	int subStepCount = 4; //스탭을 밟을때 마다 얼마나 정밀하게 계산할건지

	float timeAccumulator = 0.0f;
};