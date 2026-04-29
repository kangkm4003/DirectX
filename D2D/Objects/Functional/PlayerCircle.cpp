#include "stdafx.h"
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
	SUPER::Update();

	// 피버 모드 활성화
	if (INPUT->Down('Z'))
	if (GetFeverGauge() >= 100.f)
	{
		StartFever(10.f);
	}
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

void PlayerCircle::StartFever(float time)
{
	feverGauge = 0.f;
	inFever = true;

	SetImmute(10.f); //플레이어에게 10초 무적 추가
	immuteEnd_Dirty = true;
	GetComponent<MeshRenderer>("MeshRenderer")->SetMesh(GeometryHelper::CreateRectangle()); //사각형으로 매시 변경
	GetTransform()->SetScale(Vector2(200));
}
