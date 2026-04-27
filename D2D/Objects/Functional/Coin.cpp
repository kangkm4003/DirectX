#include "stdafx.h"
#include "Coin.h"


//Components
#include "Components/Graphic/Material.h"
#include "Components/Graphic/MeshRenderer.h"
#include "Components/Collision/CircleCollider.h"
#include "Components/Util/ScrollObject.h"
#include "Components/Transform.h"

//Utilities
#include "Utilities/GeometryHelper.h"
#include "Utilities/Random.h"


Coin::Coin(Vector2 position, Vector2 scale, Color color, UINT segments)
	: CollisionObject(position, scale, 0.f)
{
	//Component Precache
	material = make_shared<Material>(color, 0);
	meshRenderer = make_shared<MeshRenderer>();
	collider = make_shared<CircleCollider>("CircleCollider");
	scrollObject = make_shared<ScrollObject>("ScrollObject");
	transform = GetTransform();

	//Component Setup
	meshRenderer->SetMesh(GeometryHelper::CreateColorCircle(segments)); //코인 모양을 원으로 만들기 위해 MeshRenderer에 원 메쉬 설정
	meshRenderer->SetShaderSet(SHADERS->GetShader(L"./_Shaders/Vertex.hlsl", Vertex::descs));
	scrollObject->scrollSpeed = Vector2(-200.f, 0); //초당 왼쪽으로 200픽셀 이동
	scrollObject->scrollAcceleration = Vector2(-50.f, 0); //초당 왼쪽으로 50픽셀/초^2 가속

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
	if (doRespawn) //위치 재설정 (화면 오른쪽 바깥을 기준으로 랜덤한 위치에 스폰)
	{
		if (transform == nullptr) return; //Transform 컴포넌트가 없다면 위치 조정 불가능
		if (reSpawnPosMin.x > reSpawnPosMax.x || reSpawnPosMin.y > reSpawnPosMax.y) return; //랜덤 위치 범위가 이상하다면 위치 조정 불가능

		if (reSpawnPosMin == reSpawnPosMax) //랜덤 위치 범위가 하나의 점이라면 Random::Range를 사용할 필요 없이 그 점으로 위치 조정
			transform->SetPosition(reSpawnPosMin);
		else
			transform->SetPosition(Vector2(Random::Range(reSpawnPosMin.x, reSpawnPosMax.x), Random::Range(reSpawnPosMin.y, reSpawnPosMax.y)));
	}
}
