#pragma once
#include "Scene.h"
#include "Objects/ColorRect.h"

class Scene1 : public Scene
{
public:
	void Init() override;
	//void Destroy() override;

	void Update() override;
	//void Render() override;

private:
	shared_ptr<ColorRect> rect1;
	shared_ptr<ColorRect> rect2;
};