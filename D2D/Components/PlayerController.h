#pragma once
#include "Component.h"

class PlayerController : public Component
{
public:
	PlayerController(float speed = 300.0f, const string& name = "PlayerController")
		: Component(name)
	{
	}

	void Update() override;

private:
	float speed = 300.0f;
};