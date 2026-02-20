#pragma once
#include "Scene.h"

class WireCircle;
class Line;
class Transform;

class Scene2 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	//void Render() override;

private:
	float speed = 360.f; //초침이 1초당 증가할 각도 //(실제시간 = 1초당 6˚)

	//시계침들의 속도
	float R_sec = speed;
	float R_min = speed / 60.f;
	float R_hour = speed / 600.f;

	shared_ptr<WireCircle> clock_body;

	shared_ptr<Line> clock_second;
	shared_ptr<Transform> clock_second_tr;

	shared_ptr<Line> clock_minute;
	shared_ptr<Transform> clock_minute_tr;

	shared_ptr<Line> clock_hour;
	shared_ptr<Transform> clock_hour_tr;
};