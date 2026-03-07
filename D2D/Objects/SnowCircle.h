#pragma once
#include "ColorCircle.h"

class SnowCircle : public ColorCircle
{
public:
	SnowCircle(Vector2 position, Vector2 scale, Vector2 speedInput, Color color = WHITE, UINT segments = 50);
	~SnowCircle() override = default;

	void Update();
	//void Render();

private:
	float timeAfterSpawn = 0; //객체가 생성되고 경과한 시간 (프로그램 시간 기준)
	Vector2 speed;
	shared_ptr<class Transform> myTransform = this->GetTransform(); //Transform 캐싱
};