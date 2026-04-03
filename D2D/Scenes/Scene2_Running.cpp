#include "stdafx.h"
#include "Scene2_Running.h"

#include "Objects/ColorRect.h"
#include "Objects/ColorCircle.h"
#include "Objects/PlayerCircle.h"]
#include "Objects/ObjectContainer.h"

#include "Components/Jump.h"
#include "Components/Transform.h"
#include "Components/Jump.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Components/Material.h"
#include "Components/MeshRenderer.h"

#include "Utilities/Random.h"
#include "Utilities/GeometryHelper.h"

void Scene2::Init()
{
	curScrollSpeed = defaultScrollSpeed;

	Random::Init();
	playerCircle = make_unique<PlayerCircle>(Vector2(CENTER_X - 400, CENTER_Y - 200), Vector2(50), GREEN);
	playerCircle->AddComponent(make_unique<BoxCollider>());
	AddObject(playerCircle);

	floor = make_unique<ColorRect>(Vector2(CENTER_X, CENTER_Y - 300), Vector2(WIN_DEFAULT_WIDTH, 50), 0.f, WHITE);
	floor->AddComponent(make_shared<BoxCollider>());
	AddObject(floor);

	objects = make_unique<ObjectContainer>(Vector2(WIN_DEFAULT_WIDTH, 0), Vector2(0, 0), 0, 3);

	//원형 장해물
	{
		auto circleObstacle1 = make_shared<ColorCircle>(Vector2(0, 0), Vector2(50), Color(1, 0.49, 0)); //주황 원
		circleObstacle1->AddComponent(make_shared<CircleCollider>());
		auto collider = circleObstacle1->GetComponent<CircleCollider>("CircleCollider");
		auto transform = circleObstacle1->GetTransform();
		circleObstacles.push_back({collider, transform});
		objects->Add(move(circleObstacle1), Vector2(Random::Range(spawn_range.first, spawn_range.second), floor->GetTransform()->GetPosition().y + floor->GetTransform()->GetScale().y * 0.5));
	}

	//사각형 장해물
	{
		auto boxObstacle1 = make_shared<ColorRect>(Vector2(0, 0), Vector2(40, 150), 0, RED); //빨간 사각형
		boxObstacle1->AddComponent(make_shared<BoxCollider>());
		auto collider = boxObstacle1->GetComponent<BoxCollider>("BoxCollider");
		auto transform = boxObstacle1->GetTransform();
		boxObstacles.push_back({collider, transform});
		objects->Add(move(boxObstacle1), Vector2(Random::Range(spawn_range.first, spawn_range.second), floor->GetTransform()->GetPosition().y + 75));
	}

	//회전하는 장해물
	{
		auto boxObstacle2 = make_shared<ColorRect>(Vector2(0, 0), Vector2(20, 120), 0, Color(1.f, 0.f, 1.f));
		boxObstacle2->AddComponent(make_shared<BoxCollider>());
		auto collider = boxObstacle2->GetComponent<BoxCollider>("BoxCollider");
		auto transform = boxObstacle2->GetTransform();
		boxObstacles.push_back({ collider, transform });
		boxObstacle2->GetTransform()->angularVelocity = 360; //매 프레임 마다 회전할 각도값 
		objects->Add(move(boxObstacle2), Vector2(Random::Range(spawn_range.first, spawn_range.second), floor->GetTransform()->GetPosition().y + 250));
	}

	{
		int coinNumber = 5; //한 화면에 보일 코인의 최대 갯수
		
		for (int i = 0; i < coinNumber; i++)
		{
			auto coin = make_shared<ColorCircle>(Vector2(0, 0), Vector2(30), Color(1, 1, 0)); //노랑 원 (코인)
			coin->AddComponent(make_shared<CircleCollider>());
			auto collider =  coin->GetComponent<CircleCollider>("CircleCollider");
			auto transform = coin->GetTransform();
			coins.push_back({ move(collider) ,move(transform) });
			objects->Add(move(coin), Vector2(Random::Range(spawn_range.first, spawn_range.second), Random::Range(200, 400)));
		}
	}

	AddObject(objects);

	//Component cache
	playerCircleCollider = playerCircle->GetComponent<CircleCollider>("CircleCollider");
	playerBoxCollider = playerCircle->GetComponent<BoxCollider>("BoxCollider");
	playerCircleJump = playerCircle->GetComponent<Jump>("Jump");
	floorCollider = floor->GetComponent<BoxCollider>("BoxCollider");
	//

	playerCircleJump->SetMaxJumpCount(2);
}

void Scene2::Update()
{
	SUPER::Update();

	shared_ptr<Collider> playerCollider;
	if (inFever)
		playerCollider = playerBoxCollider;
	else
		playerCollider = playerCircleCollider;

	if (playerCollider->IsColliding(floorCollider) && playerCircleJump->GetonAir() && playerCircleJump->GetSpeed() <= 0) //점프 이후 하강중 바닥과 부딛힘 (한번만 연산)
	{
		playerCircle->GetComponent<Jump>("Jump")->Land();
		playerCircle->GetTransform()->SetPosition(Vector2(
			playerCircle->GetTransform()->GetPosition().x,
			floor->GetTransform()->GetPosition().y + floor->GetTransform()->GetScale().y * 0.5 + playerCircle->GetTransform()->GetScale().y * 0.5) //착지 했을때 바닥에 박히는것을 방지하기 위해 위치 재조정
		);
	}

	//점프
	if (INPUT->Down(VK_SPACE))
		playerCircle->GetComponent<Jump>("Jump")->doJump(800);

	// 피버 모드 활성화
	if (INPUT->Down('Z'))
		if (feverGauge >= 100)
			startFever(10.f);

	//장해물들 왼쪽으로 이동
	for (const auto& obj : objects->members)
	{
		if (obj->GetTransform()->GetPosition().x >= -100)
			obj->GetTransform()->Move(Vector2(curScrollSpeed * DELTA, 0));
		else
			ResetObstacle(obj->GetTransform()); //위치 재설정
	}

	//
	curScrollSpeed -= 0.9 * DELTA;

	if (score_curTime >= score_AddTime)
	{
		score += 1;
		score_curTime = 0;
	}
	else
		score_curTime += DELTA;
}

void Scene2::Render()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(gHandle, &ps);

	RECT rect = { 0 };
	rect.left = 100;
	rect.top = 100;
	rect.right = 150;
	rect.bottom = 120;

	wstring text = L"text";

	DrawTextExW(hdc, text.data(), 5, &rect, DT_LEFT, nullptr);
	EndPaint(gHandle, &ps);

	SUPER::Render();
	if (inFever)
	{
		if (feverColorCurTime >= feverColorTime)
		{
			playerCircle->GetComponent<Material>("Material")->SetColor(Random::GetColor());
			feverColorCurTime = 0;
		}
		else
			feverColorCurTime += DELTA;
	}

	if (immuteEnd_Function_Dirty)
		if (playerCircle->isImmute() != true) //dirty 되었고 무적이 아니라면 (무적시간이 끝났다면)
			Player_ImmuteEnd();

	if (inFever)
		playerCollider = playerBoxCollider;
	else
		playerCollider = playerCircleCollider;

	for (const auto& coin : coins)
	{
		if (playerCollider->IsColliding(coin.first))
		{
			int addScore = 100; //추가할 점수
			int addScrollSpeed = 9; //추가할 스크롤 속도

			if (inFever != true)
			{
				int addFever = 20; // 추가할 피버 게이지 (퍼센트)
				addFeverGauge(addFever);
			}

			score += addScore;
			curScrollSpeed -= addScrollSpeed;
			ResetObstacle(coin.second); //위치 재설정
		}
	}

	//장해물과 부딛친후 무적시간이 끝났다면 다시 장애물과 중돌 체크

	for (const auto& obstacle : boxObstacles)
	{
		if (playerCollider->IsColliding(obstacle.first))
		{
			if (inFever)
			{
				ResetObstacle(obstacle.second); //위치 재설정

				int addScore = 100; //추가할 점수
				int addScrollSpeed = 9; //추가할 스크롤 속도
				score += addScore;
				curScrollSpeed -= addScrollSpeed;
			}
			else if (playerCircle->isImmute() != true) //플레이어가 현재 무적상태가 아니라면
			{
				int damege = 1; //가할 데미지
				float immuteTime = 3.f; // 무적 시간 (초)
				Player_Dameged(damege, immuteTime);
			}
		}
	}
	//
	for (const auto& obstacle : circleObstacles)
	{
		if (playerCollider->IsColliding(obstacle.first))
		{
			if (inFever)
			{
				ResetObstacle(obstacle.second); //위치 재설정

				int addScore = 100; //추가할 점수
				int addScrollSpeed = 9; //추가할 스크롤 속도
				score += addScore;
				curScrollSpeed -= addScrollSpeed;
			}
			else if (playerCircle->isImmute() != true) //플레이어가 현재 무적상태가 아니라면
			{
				int damege = 1; //가할 데미지
				float immuteTime = 3.f; // 무적 시간 (초)
				Player_Dameged(damege, immuteTime);
			}
		}
	}
}

void Scene2::Player_Dameged(int damege, float immuteTime) //플레이어가 (데미지 or 사망) 했다면 해당하는 이벤트 실행
{
	immuteEnd_Function_Dirty = true;
	playerCircle->Damege(damege, immuteTime);
	playerCircle->GetComponent<Material>("Material")->SetColor(Color(0.f,0.f,0.f,0.f));
	curScrollSpeed = defaultScrollSpeed;
	if (playerCircle->isDead())
		Player_Dead();
}

void Scene2::Player_Dead()
{
	wstring text = L"점수 : " + to_wstring(score);
	if (MessageBox(gHandle, text.c_str(), L"RunningGame", MB_OKCANCEL) == IDOK)
	{
		Destroy();
		Init();
	}
	else
	{
		PostQuitMessage(0); //프로그램 종료
	}
}

void Scene2::ResetObstacle(shared_ptr<Transform> target) //위치 재설정
{
	target->SetPosition(Vector2(WIN_DEFAULT_WIDTH + Random::Range(100, 1000), target->GetPosition().y));
}

void Scene2::startFever(float time)
{
	if (curScrollSpeed > -1200.f)
		curScrollSpeed = -1200.f;

	feverGauge = 0.f;
	inFever = true;
	playerCircle->setImmute(10.f); //플레이어에게 10초 무적 추가
	immuteEnd_Function_Dirty = true;
	playerCircle->GetComponent<MeshRenderer>("MeshRenderer")->SetMesh(GeometryHelper::CreateRectangle()); //사각형으로 매시 변경
	playerCircle->GetTransform()->SetScale(Vector2(200));
	if (playerCircle->GetTransform()->GetPosition().y - playerCircle->GetTransform()->GetScale().y * 0.5 < floor->GetTransform()->GetPosition().y + floor->GetTransform()->GetScale().y * 0.5)
	{
		playerCircle->GetTransform()->SetPosition(Vector2(
			playerCircle->GetTransform()->GetPosition().x,
			floor->GetTransform()->GetPosition().y + floor->GetTransform()->GetScale().y * 0.5 + playerCircle->GetTransform()->GetScale().y * 0.5) //착지 했을때 바닥에 박히는것을 방지하기 위해 위치 재조정
		);
	}
}

void Scene2::Player_ImmuteEnd() //무적시간 종료 (장해물과 부딛힌 후, 혹은 피버타임 종료)
{
	immuteEnd_Function_Dirty = false; //한번만 실행

	if (inFever)
	{
		inFever = false;
		playerCircle->GetComponent<MeshRenderer>("MeshRenderer")->SetMesh(GeometryHelper::CreateColorCircle(50));
		playerCircle->GetTransform()->SetScale(Vector2(50));
		playerCircle->GetComponent<Jump>("Jump")->SetonAir(true);
		playerCircle->setImmute(3.f); //피버타임 종료후 무적시간 부여(dirty값 다시 true로 설정)
		immuteEnd_Function_Dirty = true;

		if (curScrollSpeed <= -1200.f)
			curScrollSpeed *= 0.5;
	}
	playerCircle->GetComponent<Material>("Material")->SetColor(GREEN);
}

void Scene2::Destroy()
{
	SUPER::Destroy();
	playerCircle = nullptr;
	playerCircleCollider = nullptr;
	playerBoxCollider = nullptr;
	playerCircleJump = nullptr;

	floor = nullptr;
	floorCollider = nullptr;

	objects = nullptr;
	boxObstacles.clear();
	circleObstacles.clear();
	coins.clear();			  
}
