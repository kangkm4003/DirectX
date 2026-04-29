#pragma once
#include "CollisionObject.h"

class Obstacle : public CollisionObject
{
public:
	Obstacle(Vector2 position = Vector2(), Vector2 scale = Vector2(30), float rotation = 0.f, Color color = RED);
	~Obstacle() override = default;
	
	void Update();
private:
	void onCollision(shared_ptr<Collider> target) override; //충돌했을 때의 행동

//Component Precache
private:
	shared_ptr<class Material> material;
	shared_ptr<class MeshRenderer> meshRenderer;
	shared_ptr<class ScrollObject> scrollObject;
	//shared_ptr<class Transform> transform = nullptr; //이미 CollisionObject에서 precache 되어 있음
};