#include "stdafx.h"
#include "PlayerCircle.h"
#include "Components/CircleCollider.h"
#include "Components/BoxCollider.h"
#include "Components/Jump.h"
#include "Components/MeshRenderer.h"
#include "Components/Material.h"
#include "Utilities/Random.h"
#include "Utilities/GeometryHelper.h"

PlayerCircle::PlayerCircle(Vector2 position, Vector2 scale, Color color, UINT segments)
	: ColorCircle (position, scale, color, segments)
{
	AddComponent(make_shared<CircleCollider>());
	AddComponent(make_shared<Jump>());
}

void PlayerCircle::Update()
{
	if (immuteTime > 0)
		immuteTime -= DELTA;

	if (immuteTime < epsilon) //무적 상태 종료
	{
		immuteTime = 0;
	}
	SUPER::Update();
}

void PlayerCircle::Render()
{
	SUPER::Render();
}

void PlayerCircle::Damege(int damege, float immute_time)
{
	if (immuteTime > 0) return; //아직 무적시간 이라면 무시
	curHealth -= damege;
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

bool PlayerCircle::isImmute()
{
	if (immuteTime > 0)
		return true;
	else
		return false;
}