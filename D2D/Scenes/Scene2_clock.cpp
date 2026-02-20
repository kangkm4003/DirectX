#include "stdafx.h"
#include "Scene2_clock.h"
#include "Objects/WireCircle.h"
#include "Objects/Line.h"
#include "Components/Transform.h"

// 과제: 실제 시간에 맞춰 시계침 시작지점 조정하기
void Scene2::Init()
{
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime); //실제 시간
	clock_body = make_unique<WireCircle>(CENTER, Vector2(600, 600), 0, WHITE);
	clock_second = make_unique<Line>(CENTER, Vector2(1, 250), 0, BLUE);
	clock_minute = make_unique<Line>(CENTER, Vector2(1, 150), 0, GREEN);
	clock_hour = make_unique<Line>(CENTER, Vector2(1, 75), 0, RED);

	AddObject(clock_body);
	AddObject(clock_second);
	AddObject(clock_minute);
	AddObject(clock_hour);

	//R_sec = clock_second->GetTransform()->GetScale().y * 0.5; //초침이 이동할 가상의 원의 크기(자신의 길이 / 2)
	//R_min = clock_minute->GetTransform()->GetScale().y * 0.5; //분침이 이동할 가상의 원의 크기(자신의 길이 / 2)
	//R_hour = clock_hour->GetTransform()->GetScale().y * 0.5; //시침이 이동할 가상의 원의 크기(자신의 길이 / 2)

	//캐싱
	clock_second_tr = clock_second->GetTransform();
	clock_minute_tr = clock_minute->GetTransform();
	clock_hour_tr = clock_hour->GetTransform();
}

void Scene2::Update()
{
	SUPER::Update();

	//double  angle = clock_second->GetTransform()->GetRotationRadian() + speed_rad * DELTA;
	//Vector2 result = { R_sec * sinf(angle), R_sec * cosf(angle) };
	//clock_second->GetTransform()->SetPosition(CENTER + result); //초침의 위치를 기울기에 맞춰 값 변환
	//clock_second->GetTransform()->RotateRadian(speed_rad * DELTA);
	//
	//angle = clock_minute->GetTransform()->GetRotationRadian() + speed_rad * 0.016 * DELTA;
	//result = { R_min * sinf(angle), R_min * cosf(angle) };
	//clock_minute->GetTransform()->SetPosition(CENTER + result); //분침의 위치를 기울기에 맞춰 값 변환
	//clock_minute->GetTransform()->RotateRadian(speed_rad * 0.016 * DELTA);
	//
	//angle = clock_hour->GetTransform()->GetRotationRadian() + speed_rad * 0.0016 * DELTA;
	//result = { R_hour * sinf(angle), R_hour * cosf(angle) };
	//clock_hour->GetTransform()->SetPosition(CENTER + result); //시침의 위치를 기울기에 맞춰 값 변환
	//clock_hour->GetTransform()->RotateRadian(speed_rad * 0.0016 * DELTA);

	//각 시계침들의 속도값에 맞춰 기울임 조절
	clock_second_tr->SetRotationDegree(clock_second_tr->GetRotationDegree() + R_sec * DELTA);
	clock_minute_tr->SetRotationDegree(clock_minute_tr->GetRotationDegree() + R_min * DELTA);
	clock_hour_tr->SetRotationDegree(clock_hour_tr->GetRotationDegree() + R_hour * DELTA);
}

void Scene2::Destroy()
{
	SUPER::Destroy();

	//캐싱했던 자원들 지우기
	clock_body = nullptr;
	clock_second = nullptr;
	clock_minute = nullptr;
	clock_hour = nullptr;

	clock_second_tr = nullptr;
	clock_minute_tr = nullptr;
	clock_hour_tr = nullptr;
}