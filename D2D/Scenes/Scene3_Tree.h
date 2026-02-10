#pragma once
#include "Scene.h"

class Scene3 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void Render() override;

private:
};