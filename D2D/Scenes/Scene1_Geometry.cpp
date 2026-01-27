#include "stdafx.h"
#include "Scene1_Geometry.h"
#include "Objects/WireCircle.h"
#include "Components/PlayerController.h"

void Scene1::Init()
{
	//shared_ptr<class ColorRect> rect = make_unique<ColorRect>(CENTER, Vector2(100, 100), 20.0f, BLUE);
	//rect->AddComponent(make_shared<PlayerController>());
	shared_ptr<class WireCircle> circle = make_unique<WireCircle>(CENTER, Vector2(100, 100), 20.0f, BLUE);
	AddObject(circle);
}

void Scene1::Update()
{
	SUPER::Update();
}

void Scene1::Render()
{
	SUPER::Render();
}

void Scene1::Destroy()
{
	SUPER::Destroy();
}
