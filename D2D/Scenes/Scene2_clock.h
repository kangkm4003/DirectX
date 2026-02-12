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
	float speed = 15.f;
	float R_sec;
	float R_min;
	float R_hour;
	shared_ptr<WireCircle> clock_body;
	shared_ptr<Line> clock_second;
	shared_ptr<Line> clock_minute;
	shared_ptr<Line> clock_hour;
};