#pragma once
#include "Scene.h"

class WireCircle;
class Line;

class Scene2 : public Scene
{
public:
	void Init() override;
	//void Destroy() override;

	void Update() override;
	//void Render() override;

private:
	float speed = 6.f; //초침이 1초당 증가할 각도 //(실제시간 = 1초당 6˚)
	float speed_rad = XMConvertToRadians(speed); //speed의 라디안
	float R_sec;
	float R_min;
	float R_hour;
	shared_ptr<WireCircle> clock_body;
	shared_ptr<Line> clock_second;
	shared_ptr<Line> clock_minute;
	shared_ptr<Line> clock_hour;
};