#pragma once
#include "Scene.h"

class ColorRect;
class WireCircle;
class ColorCircle;

class Scene4 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void Render() override;

private:
	shared_ptr<ColorRect> rect1;
	shared_ptr<ColorRect> rect2;
	shared_ptr<WireCircle> circle1;
	shared_ptr<WireCircle> circle2;
};