#pragma once
#include "CollisionObject.h"

class Coin : CollisionObject
{
public:
	Coin(Vector2 position = Vector2(), Vector2 scale = Vector2(30), Color color = YELLOW, UINT segments = 50);
	~Coin() override = default;

	void Update();
	void Render();

	bool doRespawn = true; //코인을 얻었을때 (무언가와 부딛혀 사라졌을때) 다시 스폰할지 여부

	//코인이 다시 스폰될 때의 좌표 랜덤스폰 지점 (화면 중앙 기준)
	Vector2 reSpawnRangeX = Vector2(300.f, 1000.f); //x
	Vector2 reSpawnRangeY = Vector2(200.f, 400.f); //y
	//
};