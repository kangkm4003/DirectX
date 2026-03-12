#include "stdafx.h"
#include "PlayerCircle.h"
#include "Components/CircleCollider.h"
#include "Components/Jump.h"
#include "Components/Material.h"

PlayerCircle::PlayerCircle(Vector2 position, Vector2 scale, Color color, UINT segments)
	: ColorCircle (position, scale, color, segments)
{
	original_color = color;
	AddComponent(make_shared<CircleCollider>());
	AddComponent(make_shared<Jump>());
}

void PlayerCircle::Update()
{
	SUPER::Update();
}

void PlayerCircle::Render()
{
	if (immuteTime > 0)
		immuteTime -= DELTA;
	if (FeverTime > 0)
		FeverTime -= DELTA;

	if (immuteTime < epsilon)
	{
		immuteTime = 0;
	}
	if (FeverTime < epsilon)
	{
		FeverTime = 0;
	}


	SUPER::Render();
}

void PlayerCircle::Damege(int damege, float immute_time)
{
	if (immuteTime > 0) return; //아직 무적시간 이라면 무시
	curHealth -= damege;
	GetComponent<Material>("Material")->SetColor(RED);
	immuteTime = immute_time;
	if (curHealth <= 0)
		Dead();
}

void PlayerCircle::Heal(int amount)
{
	curHealth += amount;
	if (curHealth > maxHealth) //회복했을시 최대 체력을 넘겼다면 최대체력 값으로 조정
		curHealth = maxHealth;
}

void PlayerCircle::Dead()
{
	dead = true;
}

void PlayerCircle::startFever(float duration)
{
	inFever = true;
	immuteTime = duration;
	feverGauge = 0.f;
}

bool PlayerCircle::isImmute()
{
	if (immuteTime > 0)
		return true;
	else
		return false;
}

bool PlayerCircle::isFever()
{
	return inFever;
}
