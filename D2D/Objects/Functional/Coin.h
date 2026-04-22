#pragma once
#include "CollisionObject.h"

class Coin : public CollisionObject
{
public:
	Coin(Vector2 position = Vector2(), Vector2 scale = Vector2(30), Color color = YELLOW, UINT segments = 50);
	~Coin() override = default;

	void Update();
	void Render();

	bool doRespawn = true; //코인을 얻었을때 (화면 밖으로 나가거나 무언가와 부딛혀 사라졌을때) 다시 스폰할지 여부

	//코인이 다시 스폰될 때의 좌표 랜덤스폰 지점 (화면 중앙 기준)
	Vector2 reSpawnPosMin = Vector2(WIN_DEFAULT_WIDTH + 300.f, 200.f); //코인이 다시 스폰될 때의 좌표 최소값 (화면 중앙 기준)
	Vector2 reSpawnPosMax = Vector2(WIN_DEFAULT_WIDTH + 1000.f, 400.f); //코인이 다시 스폰될 때의 좌표 최대값 (화면 중앙 기준)
	//
private:
	void onCollision(shared_ptr<Collider> target) override; //충돌했을 때의 행동
};