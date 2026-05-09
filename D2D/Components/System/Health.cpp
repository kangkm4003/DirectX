#include "stdafx.h"
#include "Health.h"

void Health::Update()
{
	SUPER::Update();

	if (immuteTimer > epsilon)
		immuteTimer -= DELTA;
	else if (immuteTimer < epsilon)
	{
		isImmute = false;
		immuteTimer = 0;
	}
}

void Health::Damage(int amount)
{
	if (!isImmute)
	{
		if (curHealth > minHealth)
			curHealth -= amount;
		if (curHealth <= minHealth)
			dead = true;

	}
}

void Health::Heal(int amount)
{
	if (curHealth < maxHealth)
		curHealth += amount;
	if (curHealth >= maxHealth)
		curHealth = maxHealth;
}
