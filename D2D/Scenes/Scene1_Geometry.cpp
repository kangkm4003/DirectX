#include "stdafx.h"
#include "Scene1_Geometry.h"
#include "Objects/ColorRect.h"
#include "Components/PlayerController.h"
#include "Objects/Line.h"
#include "Objects/WireCircle.h"
#include "Objects/ColorCircle.h"
#include "Utilities/Collision.h"
#include "Components/Transform.h"

//과제 : 충돌 체크 시뮬레이터, 시계 구현, 크리스마스 트리 만들기 


void Scene1::Init()
{
	rect1 = make_unique<ColorRect>(CENTER, Vector2(100, 100), 0.0f, BLUE);
	rect1->AddComponent(make_shared<PlayerController>());
	AddObject(rect1);

	rect2 = make_unique<ColorRect>(CENTER, Vector2(100, 100), 0.0f, BLUE);
	AddObject(rect2);
}

void Scene1::Update()
{
	SUPER::Update();
}

//void Scene1::Destroy()
//{
//	SUPER::Destroy();
//	//rect = nullptr;
//}
