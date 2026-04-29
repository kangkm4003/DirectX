#include "stdafx.h"
#include "Obstacle.h"

//Components
#include "Components/Graphic/Material.h"
#include "Components/Graphic/MeshRenderer.h"
#include "Components/Collision/BoxCollider.h"
#include "Components/Util/ScrollObject.h"

//Utilities
#include "Utilities/GeometryHelper.h"

Obstacle::Obstacle(Vector2 position, Vector2 scale, float rotation, Color color)
	: CollisionObject(position, scale, rotation)
{
	//Component Precache
	material = make_shared<Material>(color, 0);
	meshRenderer = make_shared<MeshRenderer>();
	collider = make_shared<BoxCollider>("BoxCollider");
	scrollObject = make_shared<ScrollObject>("ScrollObject");
	transform = GetTransform();

	//Component Setup
	meshRenderer->SetMesh(GeometryHelper::CreateRectangle()); //장애물 모양을 사각형으로 만들기 위해 MeshRenderer에 사각형 메쉬 설정
	meshRenderer->SetShaderSet(SHADERS->GetShader(L"_Shaders/Vertex.hlsl", Vertex::descs));
	scrollObject->scrollSpeed = Vector2(-200.f, 0); //초당 왼쪽으로 200픽셀 이동
	
	//Component Registration
	AddComponent(material);
	AddComponent(meshRenderer);
	AddComponent(collider);
	AddComponent(scrollObject);
}

void Obstacle::Update()
{
	SUPER::Update();
}

void Obstacle::onCollision(shared_ptr<Collider> target) //충돌했을 때의 행동
{
	if (scrollObject->doRespawn)
		scrollObject->ResetPosition(); //위치 재설정 (화면 오른쪽 바깥을 기준으로 랜덤한 위치에 스폰) (doRespawn이 false 일땐 실행 하여도 위치값 변화 없음)
}