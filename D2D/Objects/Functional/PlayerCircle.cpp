#include "stdafx.h"
#include "PlayerCircle.h"

#include "Components/Collision/CircleCollider.h"
#include "Components/Collision/BoxCollider.h"
#include "Components/Graphic/Material.h"
#include "Components/Graphic/MeshRenderer.h"
#include "Components/Transform.h"
#include "Components/Input/Jump.h"
#include "Components/System/Health.h"
#include "Components/Input/Fever.h"

#include "Utilities/Random.h"
#include "Utilities/GeometryHelper.h"

//ToDo: PlayerCircle의 기능들 컴포넌트화 및 구현 하기
/*
	jump = 끝
	fever
	health
*/

PlayerCircle::PlayerCircle(Vector2 position, Vector2 scale, Color color, UINT segments)
	: CollisionObject(position, scale, 0)
{
	//Component Precache
	material = make_shared<Material>(color, 0);
	meshRenderer = make_shared<MeshRenderer>();
	circleCollider = make_shared<CircleCollider>();
	boxCollider = make_shared<BoxCollider>();
	jump = make_shared<Jump>();

	//Component Setup
	meshRenderer->SetMesh(GeometryHelper::CreateColorCircle(segments)); //원으로 만들기 위해 MeshRenderer에 원 메쉬 설정
	meshRenderer->SetShaderSet(SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));
	jump->maxJumpCount = 2; //최대점프횟수를 2회로 설정 (이단점프)
	
	jump->SetMappingKey(jumpKey);

	originalColor = color;

	//Component Registration
	AddComponent(circleCollider);
	AddComponent(boxCollider);
	AddComponent(jump);
}
void PlayerCircle::DoJump(float amount)
{
	if (curJumpCount <= maxJumpCount)
	{
		onAir = true;
		speed = amount;
		curJumpCount += 1;
	}
}

void PlayerCircle::Update()
{
	SUPER::Update();

	if (!health->GetisImmute() && immuteEnd_Dirty) ImmuteEnd(); //무적시간 종료

	if (INPUT->Down(jumpKey))
	{
		if (curJumpCount <= maxJumpCount)
		{
			DoJump(800.f);
		}
	}
}

void PlayerCircle::Render()
{
	SUPER::Render();
}

void PlayerCircle::onCollision(shared_ptr<Collider> target, shared_ptr<Transform> targetTransform) //장해물과 부딪힘. 무적상태가 아니라면 플레이어에게 데미지
{
	if (jump->GetOnAir())
		jump->Land(targetTransform);

	if (!health->GetisImmute())
	{
		material->SetColor(damegeColor); //플레이어의 색상을 데미지를 입었을시에 색상으로 변경
		health->Damage(1); //데미지
		health->SetImmute(2.f);
		immuteEnd_Dirty = true; //무적시간 종료를 Update함수에서 확인 하기 때문에 1회만 실행하기 위해서 Dirty값을 활용 
	}
}

void PlayerCircle::DoJump(float amount)
{
}

void PlayerCircle::StartFever()
{
	meshRenderer->SetMesh(GeometryHelper::CreateRectangle());
	transform->SetScale(transform->GetScale() * 2); //피버 시작시 원본 크기의 2배로 설정
}

void PlayerCircle::ImmuteEnd()
{
	immuteEnd_Dirty = false; //Dirty값을 false로 변경해 함수가 매 Update마다 실행되는것을 방지
	material->SetColor(originalColor); //원래 색상으로 돌아감
}
