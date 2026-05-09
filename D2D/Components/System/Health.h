#pragma once
#include "Components/Component.h"

class Health : public Component
{
public:
	Health(const string& name = "Health")
		: Component(name)
	{
	}

	void Update();

	void Damage(int amount);
	void Heal(int amount);
	int GetCurHealth() const { return curHealth; }

	bool isDead() const { return dead; }

	void SetImmute(int time) { immuteTimer = time; isImmute = true; }
	bool GetisImmute() const { return isImmute; }

private:
	int maxHealth = 3;
	int minHealth = 0;
	int curHealth = maxHealth;
	bool dead = false;
	bool isImmute = false;
	float immuteTimer = 0.f;
	
};
