
#pragma once
#include "Component.h"

class Controller : public Component
{
public:
	Controller(float speed = 300.0f, const string& name = "Controller")
		: Component(name)
	{
	}

	void Update() override;

private:
	float speed = 300.0f;
};
