#include "stdafx.h"
#include "Health.h"

void Health::Damege(int damege, float immute_time)
{
	if (immuteTime > 0) return; //아직 무적시간 이라면 무시
	curHealth -= damege;
	immuteTime = immute_time;
	if (curHealth <= 0)
		Dead();
	GetComponent<Material>("Material")->SetColor(damegeColor);
	immuteEnd_Dirty = true;
}

void Health::Heal(int amount)
{
	curHealth += amount;
	if (curHealth > maxHealth) //회복했을시 최대 체력을 넘겼다면 최대체력 값으로 조정
		curHealth = maxHealth;
}

void Health::Dead()
{
	dead = true;
}

void Health::Update()
{
	if (immuteTime > 0)
		immuteTime -= DELTA;

	if (immuteTime < epsilon) //무적 상태 종료
	{
		immuteTime = 0;
	}
}

bool Health::isImmute()
{
	if (immuteTime > 0)
		return true;
	else
		return false;
}

void Health::ImmuteEnd()
{
	if (inFever)
	{
		inFever = false;
		immuteEnd_Dirty = true;

		GetComponent<MeshRenderer>("MeshRenderer")->SetMesh(GeometryHelper::CreateColorCircle(50));
		GetTransform()->SetScale(Vector2(50));
		GetComponent<Jump>("Jump")->SetonAir(true);
		SetImmute(3.f); //피버타임 종료후 무적시간 부여(dirty값 다시 true로 설정)
	}
	GetComponent<Material>("Material")->SetColor(origianlColor);
}