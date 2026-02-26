#pragma once
#include "Scene.h"

class ColorRect;
class Scene5 : public Scene
{
public:
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;

private:
	b2WorldId worldId = b2_nullWorldId;

	shared_ptr<ColorRect> boxObj;

	b2BodyId boxBodyId = b2_nullBodyId;
	b2BodyId groundBodyId = b2_nullBodyId;

	float timeScale = 1.f; //시간이 흘러가는 배율
	int subStepCount = 4; //스탭을 밟을때 마다 얼마나 정밀하게 계산할건지
};