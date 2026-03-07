#include "stdafx.h"
#include "Scene1_Running.h"
#include "Objects/ColorRect.h"
#include "Components/Jump.h"
#include "Objects/Line.h"
#include "Objects/WireCircle.h"
#include "Objects/ColorCircle.h"
#include "Utilities/Collision.h"
#include "Components/Transform.h"
#include "Components/Jump.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Objects/ObjectContainer.h"
#include "Utilities/Random.h"

//과제 : 충돌 체크 시뮬레이터, 시계 구현, 크리스마스 트리 만들기 


void Scene1::Init()
{
	Random::Init();

	playerCircle = make_unique<ColorCircle>(Vector2(CENTER_X - 400, CENTER_Y - 200), Vector2(50), GREEN);
	playerCircle->AddComponent(make_shared<Jump>());
	playerCircle->AddComponent(make_shared<CircleCollider>());
	AddObject(playerCircle);

	floor = make_unique<ColorRect>(Vector2(CENTER_X, CENTER_Y - 300), Vector2(WIN_DEFAULT_WIDTH, 50), 0.f, WHITE);
	floor->AddComponent(make_shared<BoxCollider>());
	AddObject(floor);

	obstacles = make_unique<ObjectContainer>(Vector2(WIN_DEFAULT_WIDTH, 0), Vector2(0, 0), 0, 3);

	auto object1 = make_shared<ColorCircle>(Vector2(0, 0), Vector2(50), Color(1, 0.49, 0)); //주황 원
	object1->AddComponent(make_shared<CircleCollider>("Collider"));

	auto object2 = make_shared<ColorRect>(Vector2(0, 0), Vector2(40, 150), 0, RED); //빨간 사각형
	object1->AddComponent(make_shared<BoxCollider>("Collider"));

	auto object3 = make_shared<ColorRect>(Vector2(0, 0), Vector2(20, 120), 0, Color(1.f, 0.f, 1.f));
	object3->AddComponent(make_shared<BoxCollider>("Collider"));

	obstacles->Add(move(object1), Vector2(Random::Range(100, 1000), floor->GetTransform()->GetPosition().y + floor->GetTransform()->GetScale().y * 0.5));

	obstacles->Add(move(object2), Vector2(Random::Range(100, 1000), floor->GetTransform()->GetPosition().y + 75));

	obstacles->Add(move(object3), Vector2(Random::Range(100, 1000), floor->GetTransform()->GetPosition().y + 250));

	AddObject(obstacles);

	playerCircleCollider = playerCircle->GetComponent<CircleCollider>("Collider");
	playerCircleJump = playerCircle->GetComponent<Jump>("Jump");

	floorCollider = floor->GetComponent<BoxCollider>("Collider");

	playerCircleJump->SetMaxJumpCount(2);


}

void Scene1::Update()
{
	SUPER::Update();

	if (playerCircleCollider->IsColliding(floorCollider) && playerCircleJump->GetonAir() && playerCircleJump->GetSpeed() <= 0) //바닥과 부딛힘 (한번만 연산)
	{
		playerCircle->GetComponent<Jump>("Jump")->Land();
		playerCircle->GetTransform()->SetPosition(Vector2(
			playerCircle->GetTransform()->GetPosition().x,
			floor->GetTransform()->GetPosition().y + floor->GetTransform()->GetScale().y * 0.5 + playerCircle->GetTransform()->GetScale().y * 0.5) //착지 했을때 바닥에 박히는것을 방지하기 위해 위치 재조정
		);
	}

	if (INPUT->Down(VK_SPACE))
	{
		playerCircle->GetComponent<Jump>("Jump")->doJump(800);
	}


	for (const auto& obj : obstacles->members)
	{
		if (obj->GetTransform()->GetPosition().x >= -100)
			obj->GetTransform()->Move(Vector2(curScrollSpeed * DELTA, 0));
		else
			obj->GetTransform()->SetPosition(Vector2(WIN_DEFAULT_WIDTH + Random::Range(100, 1000), obj->GetTransform()->GetPosition().y));
	}
	obstacles->members[2]->GetTransform()->RotateDegree(360 * DELTA);
	curScrollSpeed -= 0.3 + DELTA;
}

void Scene1::Destroy()
{
	SUPER::Destroy();
	playerCircle = nullptr;
	playerCircleCollider = nullptr;
	floor = nullptr;
	floorCollider = nullptr;
	obstacles = nullptr;
}
