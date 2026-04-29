#pragma once
#include "CollisionObject.h"

class Coin : public CollisionObject
{
public:
	Coin(Vector2 position = Vector2(), Vector2 scale = Vector2(30), Color color = YELLOW, UINT segments = 50);
	~Coin() override = default;

	void Update();
	void Render();

private:
	void onCollision(shared_ptr<Collider> target) override;

	//Component Precache
private:
	shared_ptr<class Material> material;
	shared_ptr<class MeshRenderer> meshRenderer;
	shared_ptr<class ScrollObject> scrollObject;
};