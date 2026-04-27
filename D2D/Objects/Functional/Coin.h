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

	void onCollision(shared_ptr<Collider> target) override;

//Component Precache
private:
	shared_ptr<class Material> material = nullptr;
	shared_ptr<class MeshRenderer> meshRenderer = nullptr;
	shared_ptr<class ScrollObject> scrollObject = nullptr;
	//shared_ptr<class Transform> transform = nullptr; //이미 CollisionObject에서 precache 되어 있음
};