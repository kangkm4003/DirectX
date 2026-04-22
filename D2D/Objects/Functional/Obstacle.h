#pragma once
#include "CollisionObject.h"

class Obstacle : public CollisionObject
{
	public:
	Obstacle(Vector2 position = Vector2(), Vector2 scale = Vector2(30), float rotation = 0.f);
	~Obstacle() override = default;
	
	void Update();
	void Render();

private:
	void onCollision(shared_ptr<Collider> target) override; //충돌했을 때의 행동

//variables
public:
	Vector2 scrollSpeed = Vector2( //오브젝트가 스크롤되는 속도값
		-300.f, //음수값 : 왼쪽으로 스크롤, 양수값 : 오른쪽으로 스크롤
		0.f //음수값 : 아래쪽으로 스크롤, 양수값 : 위쪽으로 스크롤
	);
};