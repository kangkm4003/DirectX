#include "stdafx.h"
#include "Coin.h"


//Components
#include "Components/Graphic/Material.h"
#include "Components/Graphic/MeshRenderer.h"
#include "Components/Collision/CircleCollider.h"
#include "Components/Util/ScrollObject.h"

//Utilities
#include "Utilities/GeometryHelper.h"


Coin::Coin(Vector2 position, Vector2 scale, Color color, UINT segments)
	: CollisionObject(position, scale, 0.f)
{
	//Component Precache
	material = make_shared<Material>(color, 0);
	meshRenderer = make_shared<MeshRenderer>();
	collider = make_shared<CircleCollider>("CircleCollider");
	scrollObject = make_shared<ScrollObject>("ScrollObject");

	//Component Setup
	meshRenderer->SetMesh(GeometryHelper::CreateColorCircle(segments)); //코인 모양을 원으로 만들기 위해 MeshRenderer에 원 메쉬 설정
	meshRenderer->SetShaderSet(SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));
	scrollObject->scrollSpeed = Vector2(-200.f, 0); //초당 왼쪽으로 200픽셀 이동
	
	//Component Registration
	AddComponent(material);
	AddComponent(meshRenderer);
	AddComponent(collider);
	AddComponent(scrollObject);
}

void Coin::Update()
{
	SUPER::Update();
}

void Coin::Render()
{
	SUPER::Render();
}

void Coin::onCollision(shared_ptr<Collider> target) //충돌했을 때의 행동
{
	if (scrollObject->doRespawn)
		scrollObject->ResetPosition(); //위치 재설정 (화면 오른쪽 바깥을 기준으로 랜덤한 위치에 스폰) (doRespawn이 false 일땐 실행 하여도 위치값 변화 없음)
}
