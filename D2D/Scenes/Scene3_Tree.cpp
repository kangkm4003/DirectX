#include "stdafx.h"
#include "Objects/ObjectGroup.h"
#include "Objects/ColorCircle.h"
#include "Objects/ColorRect.h"
#include "Scene3_Tree.h"

void Scene3::Init()
{
	//나무
	TreeObject_Group = make_unique<ObjectGroup>(CENTER, Vector2(1, 1), 0, 4);

	shared_ptr<ColorRect> treeLeaf0 = make_unique<ColorRect>(Vector2(0, 0), Vector2(100, 100), 0.f, GREEN);
	shared_ptr<ColorRect> treeLeaf1 = make_unique<ColorRect>(Vector2(0, 0), Vector2(150, 100), 0.f, GREEN);
	shared_ptr<ColorRect> treeLeaf2 = make_unique<ColorRect>(Vector2(0, 0), Vector2(200, 100), 0.f, GREEN);

	shared_ptr<ColorRect> treeBody = make_unique<ColorRect>(Vector2(0, 0), Vector2(40, 100), 0.f, Color(0.6f, 0.4f, 0.2f, 1.f));

	TreeObject_Group->Add(move(treeLeaf0), Vector2(0,50));
	TreeObject_Group->Add(move(treeLeaf1), Vector2(0, -50));
	TreeObject_Group->Add(move(treeLeaf2), Vector2(0, -150));
	TreeObject_Group->Add(move(treeBody), Vector2(0, -250));

	//나무 위에 있는 빚나는 뭐시기
	Star_Group = make_unique<ObjectGroup>(CENTER, Vector2(1, 1), 0, 4);

	//shared_ptr<ColorRect> treeLeaf0 = make_unique<ColorRect>(Vector2(0, 0), Vector2(100, 100), 0.f, YELLOW);


	//선물1
	Gift1_Group = make_unique<ObjectGroup>(Vector2(CENTER.x - 90, CENTER.y - 270), Vector2(1, 1), 0, 3);

	shared_ptr<ColorRect> Gift1_Box = treeLeaf0 = make_unique<ColorRect>(Vector2(0, 0), Vector2(75, 75), 0.f, RED);
	shared_ptr<ColorRect> Gift1_Tie1 = treeLeaf0 = make_unique<ColorRect>(Vector2(0, 0), Vector2(10, 75), 0.f, YELLOW);
	shared_ptr<ColorRect> Gift1_Tie2 = treeLeaf0 = make_unique<ColorRect>(Vector2(0, 0), Vector2(75, 10), 0.f, YELLOW);

	Gift1_Group->Add(move(Gift1_Box), Vector2(0, 0));
	Gift1_Group->Add(move(Gift1_Tie1), Vector2(0, 0));
	Gift1_Group->Add(move(Gift1_Tie2), Vector2(0, 0));


	//선물2
	Gift2_Group = make_unique<ObjectGroup>(Vector2(CENTER.x + 100, CENTER.y - 285), Vector2(1, 1), 0, 3);

	shared_ptr<ColorRect> Gift2_Box = treeLeaf0 = make_unique<ColorRect>(Vector2(0, 0), Vector2(60, 60), 0.f, BLUE);
	shared_ptr<ColorRect> Gift2_Tie1 = treeLeaf0 = make_unique<ColorRect>(Vector2(0, 0), Vector2(10, 60), 0.f, WHITE);
	shared_ptr<ColorRect> Gift2_Tie2 = treeLeaf0 = make_unique<ColorRect>(Vector2(0, 0), Vector2(60, 10), 0.f, WHITE);

	Gift2_Group->Add(move(Gift2_Box), Vector2(0, 0));
	Gift2_Group->Add(move(Gift2_Tie1), Vector2(0, 0));
	Gift2_Group->Add(move(Gift2_Tie2), Vector2(0, 0));

	AddObject(TreeObject_Group);
	AddObject(Gift1_Group);
	AddObject(Gift2_Group);
}

void Scene3::Destroy()
{
	SUPER::Destroy();
	TreeObject_Group = nullptr;
	Gift1_Group = nullptr;
	Gift2_Group = nullptr;
}

void Scene3::Update()
{
	SUPER::Update();
}