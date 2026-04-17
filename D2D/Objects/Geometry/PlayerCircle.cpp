#include "stdafx.h"
#include "ObjectContainer.h"
#include "PlayerCircle.h"

#include "Components/Collision/CircleCollider.h"
#include "Components/Collision/BoxCollider.h"
#include "Components/Graphic/Material.h"
#include "Components/Graphic/MeshRenderer.h"
#include "Components/Transform.h"
#include "Components/Input/Jump.h"

#include "Utilities/Random.h"
#include "Utilities/GeometryHelper.h"

PlayerCircle::PlayerCircle(Vector2 position, Vector2 scale, Color color, UINT segments)
	: ColorCircle (position, scale, color, segments)
{
	AddComponent(make_shared<CircleCollider>());
	AddComponent(make_unique<BoxCollider>());
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

	if (inFever)
	{
		if (feverColorTimer >= feverColorTime)
		{
			GetComponent<Material>("Material")->SetColor(Random::GetColor());
			feverColorTimer = 0;
		}
		else
			feverColorTimer += DELTA;
	}
}

void PlayerCircle::Damege(int damege, float immute_time)
{
	if (immuteTime > 0) return; //아직 무적시간 이라면 무시
	curHealth -= damege;
	immuteTime = immute_time;
	if (curHealth <= 0)
		Dead();
	GetComponent<Material>("Material")->SetColor(damegeColor);
	immuteEnd_Dirty = true;
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

void PlayerCircle::ImmuteEnd()
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

void PlayerCircle::StartFever(float time)
{
	feverGauge = 0.f;
	inFever = true;

	SetImmute(10.f); //플레이어에게 10초 무적 추가
	immuteEnd_Dirty = true;
	GetComponent<MeshRenderer>("MeshRenderer")->SetMesh(GeometryHelper::CreateRectangle()); //사각형으로 매시 변경
	GetTransform()->SetScale(Vector2(200));
}
