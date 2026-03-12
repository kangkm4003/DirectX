#include "stdafx.h"
#include "Scene2_Running.h"
#include "Objects/ColorRect.h"
#include "Components/Jump.h"
#include "Objects/ColorCircle.h"
#include "Objects/PlayerCircle.h"]
#include "Components/Transform.h"
#include "Components/Jump.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Objects/ObjectContainer.h"
#include "Components/Material.h"
#include "Utilities/Random.h"

//과제 : 충돌 체크 시뮬레이터, 시계 구현, 크리스마스 트리 만들기 


void Scene2::Init()
{
	scrollSpeed = -450.f;
	curScrollSpeed = scrollSpeed;

	Random::Init();
	playerCircle = make_unique<PlayerCircle>(Vector2(CENTER_X - 400, CENTER_Y - 200), Vector2(50), GREEN);
	AddObject(playerCircle);

	floor = make_unique<ColorRect>(Vector2(CENTER_X, CENTER_Y - 300), Vector2(WIN_DEFAULT_WIDTH, 50), 0.f, WHITE);
	floor->AddComponent(make_shared<BoxCollider>());
	AddObject(floor);

	objects = make_unique<ObjectContainer>(Vector2(WIN_DEFAULT_WIDTH, 0), Vector2(0, 0), 0, 3);

	auto circleObstacle1 = make_shared<ColorCircle>(Vector2(0, 0), Vector2(50), Color(1, 0.49, 0)); //주황 원
	circleObstacle1->AddComponent(make_shared<CircleCollider>());
	circleObstacles.push_back(move(circleObstacle1->GetComponent<CircleCollider>("Collider")));
	objects->Add(move(circleObstacle1), Vector2(Random::Range(spawn_range.first, spawn_range.second), floor->GetTransform()->GetPosition().y + floor->GetTransform()->GetScale().y * 0.5));

	auto boxObstacle1 = make_shared<ColorRect>(Vector2(0, 0), Vector2(40, 150), 0, RED); //빨간 사각형
	boxObstacle1->AddComponent(make_shared<BoxCollider>());
	boxObstacles.push_back(move(boxObstacle1->GetComponent<BoxCollider>("Collider")));
	objects->Add(move(boxObstacle1), Vector2(Random::Range(spawn_range.first, spawn_range.second), floor->GetTransform()->GetPosition().y + 75));

	auto boxObstacle2 = make_shared<ColorRect>(Vector2(0, 0), Vector2(20, 120), 0, Color(1.f, 0.f, 1.f));
	boxObstacle2->AddComponent(make_shared<BoxCollider>());
	boxObstacles.push_back(move(boxObstacle2->GetComponent<BoxCollider>("Collider")));
	boxObstacle2->GetTransform()->angularVelocity = 360; //매 프레임 마다 회전할 각도값 
	objects->Add(move(boxObstacle2), Vector2(Random::Range(spawn_range.first, spawn_range.second), floor->GetTransform()->GetPosition().y + 250));

	{
		auto coin1 = make_shared<ColorCircle>(Vector2(0, 0), Vector2(30), Color(1, 1, 0)); //노랑 원 (코인)
		coin1->AddComponent(make_shared<CircleCollider>());
		auto collider =  coin1->GetComponent<CircleCollider>("Collider");
		auto transform = coin1->GetTransform();
		coins.push_back(pair(move(collider), move(transform)));
		objects->Add(move(coin1), Vector2(Random::Range(spawn_range.first, spawn_range.second), Random::Range(200, 400)));
	}

	{
		auto coin2 = make_shared<ColorCircle>(Vector2(0, 0), Vector2(30), Color(1, 1, 0)); //노랑 원 (코인)
		coin2->AddComponent(make_shared<CircleCollider>());
		auto collider = coin2->GetComponent<CircleCollider>("Collider");
		auto transform = coin2->GetTransform();
		coins.push_back(pair(move(collider), move(transform)));
		objects->Add(move(coin2), Vector2(Random::Range(spawn_range.first, spawn_range.second), Random::Range(200, 400)));
	}

	AddObject(objects);

	playerCircleCollider = playerCircle->GetComponent<CircleCollider>("Collider");
	playerCircleJump = playerCircle->GetComponent<Jump>("Jump");

	floorCollider = floor->GetComponent<BoxCollider>("Collider");

	playerCircleJump->SetMaxJumpCount(2);


}

void Scene2::Update()
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
	if (INPUT->Down('Z'))
		if (playerCircle->getFeverGauge() >= 100)
		{
			playerCircle->startFever(5.f);
			Player_Fever();
		}

	for (const auto& obj : objects->members)
	{
		if (obj->GetTransform()->GetPosition().x >= -100)
			obj->GetTransform()->Move(Vector2(curScrollSpeed * DELTA, 0));
		else
			obj->GetTransform()->SetPosition(Vector2(WIN_DEFAULT_WIDTH + Random::Range(100, 1000), obj->GetTransform()->GetPosition().y));
	}

	for (const auto& coin : coins)
		if (playerCircleCollider->IsColliding(coin))
		{
			int damege = 100; //추가할 점수
			int immuteTime = 20; // 추가할 무적 게이지 (퍼센트)
		}

	//무적시간이 끝났다면 장애물과 중동 체크

	if (playerCircle->isImmute() != true)
	{
		for (const auto& obstacle : boxObstacles)
			if (playerCircleCollider->IsColliding(obstacle))
			{
				int damege = 1; //가할 데미지
				float immuteTime = 3.f; // 무적 시간
				playerCircle->Damege(damege, immuteTime);
				Player_Dameged();
			}
		//
		for (const auto& obstacle : circleObstacles)
			if (playerCircleCollider->IsColliding(obstacle))
			{
				int damege = 1; //가할 데미지
				float immuteTime = 3.f; // 무적 시간
				playerCircle->Damege(damege, immuteTime);
				Player_Dameged();
			}
		//
	}
	else if (playerCircle->isImmute() && playerCircle->isFever())
	{
		for (const auto& obstacle : boxObstacles)
			if (playerCircleCollider->IsColliding(obstacle))
			{
				obstacle->GetTransform()->SetPosition(Vector2(WIN_DEFAULT_WIDTH + Random::Range(100, 1000), obj->GetTransform()->GetPosition().y));
			}
		//
		for (const auto& obstacle : circleObstacles)
			if (playerCircleCollider->IsColliding(obstacle))
			{

			}
		//
	}
	curScrollSpeed -= 0.3 + DELTA;
}

void Scene2::Render()
{
	SUPER::Render();
}

void Scene2::Player_Dameged() //플레이어가 (데미지 or 사망) 했다면 (혹은 시도했다면) 해당하는 이벤트 실행
{
	curScrollSpeed = scrollSpeed;
	if (playerCircle->isDead())
		Player_Dead();

}

void Scene2::Player_Dead()
{
	if (MessageBox(gHandle, L"test text", L"WinAPI", MB_OKCANCEL) == IDOK)
	{
		Destroy();
		Init();
	}
	else
	{
		PostQuitMessage(0);
	}
}

void Player_Fever()
{

}

void Scene2::Destroy()
{
	SUPER::Destroy();
	playerCircle = nullptr;
	playerCircleCollider = nullptr;
	floor = nullptr;
	floorCollider = nullptr;
	objects = nullptr;
	boxObstacles.clear();
	circleObstacles.clear();
	coins.clear();
}
