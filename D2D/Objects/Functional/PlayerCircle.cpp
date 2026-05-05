#include "stdafx.h"
#include "PlayerCircle.h"

#include "Components/Collision/CircleCollider.h"
#include "Components/Collision/BoxCollider.h"
#include "Components/Graphic/Material.h"
#include "Components/Graphic/MeshRenderer.h"
#include "Components/Transform.h"
#include "Components/Input/Jump.h"
#include "Components/System/Health.h"

#include "Utilities/Random.h"
#include "Utilities/GeometryHelper.h"

//ToDo: Health 시스템을 만들되 Material 및 mesh 변경은 PlayerCircle 에서 실행하게 만들기

PlayerCircle::PlayerCircle(Vector2 position, Vector2 scale, Color color, UINT segments)
	: CollisionObject(position, scale, 0)
{
	//Component Precache
	material = make_shared<Material>(color, 0);
	meshRenderer = make_shared<MeshRenderer>();
	circleCollider = make_shared<CircleCollider>();
	boxCollider = make_shared<BoxCollider>();
	jump = make_shared<Jump>();
	health = make_shared<Health>();

	//Component Setup
	meshRenderer->SetMesh(GeometryHelper::CreateColorCircle(segments)); //원으로 만들기 위해 MeshRenderer에 원 메쉬 설정
	meshRenderer->SetShaderSet(SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));
	jump->maxJumpCount = 2;

	//Component Registration
	AddComponent(circleCollider);
	AddComponent(boxCollider);
	AddComponent(health);
	AddComponent(jump);
}

void PlayerCircle::Update()
{
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

void PlayerCircle::onCollision(shared_ptr<Collider> target)
{
	GetComponent<Material>("Material")->SetColor(damegeColor);
}

void PlayerCircle::DoJump(float amount)
{
	jump->DoJump(amount);
}
