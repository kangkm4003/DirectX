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
	rect2 = make_unique<ColorRect>(CENTER + Vector2(300, 300), Vector2(100, 100), 0, RED);
	circle1 = make_unique<ColorCircle>(CENTER + Vector2(-300, -300), Vector2(100, 100), 0, RED);
	circle2 = make_unique<WireCircle>(CENTER + Vector2(-300, +300), Vector2(100, 100), 0, RED);

	rect1->AddComponent(make_shared<PlayerController>());
	rect1->AddComponent(make_shared<BoxCollider>());
	AddObject(rect1);
	AddObject(rect2);
	AddObject(circle1);
	AddObject(circle2);
}

void Scene4::Update()
{
	SUPER::Update();
	//직사각형 끼리의 충돌
	//if (rect1->GetComponent<BoxCollider>("Collider")->IsCollidingWith(ColliderType::BOX, rect2->GetTransform()->GetPosition(), rect2->GetTransform()->GetScale()))
	//	rect1->GetComponent<Material>("Material")->SetColor(Color(1, 0, 1, 1));

	//직사각형, 원 충돌
	if (rect1->GetComponent<BoxCollider>("Collider")->IsCollidingWith(ColliderType::CIRCLE, circle1->GetTransform()->GetPosition(), circle1->GetTransform()->GetScale()))
		circle1->GetComponent<Material>("Material")->SetColor(MAGENTA);
	else
		circle1->GetComponent<Material>("Material")->SetColor(RED);
	
	//원, 원 충돌
	if (rect1->GetComponent<BoxCollider>("Collider")->IsCollidingWith(ColliderType::CIRCLE, circle2->GetTransform()->GetPosition(), circle2->GetTransform()->GetScale()))
		circle2->GetComponent<Material>("Material")->SetColor(MAGENTA);
	else
		circle2->GetComponent<Material>("Material")->SetColor(RED);
	
	//직사각형 끼리의 충돌(OBB)
	if (rect1->GetComponent<BoxCollider>("Collider")->IsCollidingWithOBB(rect2->GetTransform()))
		rect2->GetComponent<Material>("Material")->SetColor(MAGENTA);
	else
		rect2->GetComponent<Material>("Material")->SetColor(RED);
}