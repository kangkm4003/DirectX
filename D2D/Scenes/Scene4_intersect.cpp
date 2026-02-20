#include "stdafx.h"
#include "Scene4_Intersect.h"

#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Components/PlayerController.h"
#include "Components/Material.h"
#include "Components/Transform.h"

#include "Objects/ColorRect.h"
#include "Objects/ColorCircle.h"
#include "Objects/WireCircle.h"

void Scene4::Init()
{
	rect1 = make_unique<ColorRect>(CENTER, Vector2(100, 100), 0, BLUE);
	rect1->AddComponent(make_shared<PlayerController>());
	rect1->AddComponent(make_shared<BoxCollider>());
	AddObject(rect1);

	rect2 = make_unique<ColorRect>(CENTER + Vector2(300, 300), Vector2(100, 100), 0, RED);
	rect2->AddComponent(make_shared<BoxCollider>());
	AddObject(rect2);

	circle1 = make_unique<ColorCircle>(CENTER + Vector2(-300, -300), Vector2(100, 100), 0, RED);
	circle1->AddComponent(make_shared<CircleCollider>());
	AddObject(circle1);
	
	circle2 = make_unique<WireCircle>(CENTER + Vector2(-300, +300), Vector2(100, 100), 0, RED);
	circle2->AddComponent(make_shared<CircleCollider>());
	AddObject(circle2);

	//히트박스 컴포넌트 참조 캐싱
	rect1HitBox = rect1->GetComponent<BoxCollider>("Collider");
	rect2HitBox = rect2->GetComponent<BoxCollider>("Collider");
	circle1HitBox = circle1->GetComponent<CircleCollider>("Collider");
	circle2HitBox = circle2->GetComponent<CircleCollider>("Collider");
}

void Scene4::Destroy()
{
	SUPER::Destroy();

	rect1 = nullptr;
	rect2 = nullptr;
	circle1 = nullptr;
	circle2 = nullptr;

	rect1HitBox = nullptr;
	rect2HitBox = nullptr;
	circle1HitBox = nullptr;
	circle2HitBox = nullptr;
}

void Scene4::Update()
{
	SUPER::Update();

	//직사각형, 원1 충돌
	if (rect1HitBox->IsColliding(circle1HitBox))
		circle1->GetComponent<Material>("Material")->SetColor(MAGENTA);
	else
		circle1->GetComponent<Material>("Material")->SetColor(RED);
	
	//직사각형, 원2 충돌
	if (rect1HitBox->IsColliding(circle2HitBox))
		circle2->GetComponent<Material>("Material")->SetColor(MAGENTA);
	else
		circle2->GetComponent<Material>("Material")->SetColor(RED);
	
	//직사각형 끼리의 충돌(OBB 포함)
	if (rect1HitBox->IsColliding(rect2HitBox))
		rect2->GetComponent<Material>("Material")->SetColor(MAGENTA);
	else
		rect2->GetComponent<Material>("Material")->SetColor(RED);
}