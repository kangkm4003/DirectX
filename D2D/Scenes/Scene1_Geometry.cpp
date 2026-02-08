#include "stdafx.h"
#include "Scene1_Geometry.h"
#include "Objects/ColorRect.h"
#include "Components/PlayerController.h"
#include "Objects/Line.h"
#include "Objects/WireCircle.h"
#include "Objects/ColorCircle.h"
#include "Utilities/Collision.h"
#include "Components/Transform.h"

void Scene1::Init()
{
	rect1 = make_unique<ColorRect>(CENTER, Vector2(100, 100), 0.0f, BLUE);
	rect1->AddComponent(make_shared<PlayerController>());
	AddObject(rect1);

	rect2 = make_unique<ColorRect>(CENTER, Vector2(100, 100), 0.0f, BLUE);
	AddObject(rect2);

	//AddObject(make_shared<Line>(CENTER, 300.0f, 0.0f, MAGENTA));
	//AddObject(make_shared<WireCircle>(CENTER, Vector2(100, 100), 0.0f, YELLOW));
	//AddObject(make_shared<ColorCircle>(CENTER - Vector2(0, 100), Vector2(100, 100), 0.0f, CYAN));
}

void Scene1::Update()
{
	SUPER::Update();

	std::cout << "x:" << rect1->GetTransform()->right.x + rect1->GetTransform()->up.x << std::endl;
}

//void Scene1::Destroy()
//{
//	SUPER::Destroy();
//	//rect = nullptr;
//}
