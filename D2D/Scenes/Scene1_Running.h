#pragma once
#include "Scene.h"

class Scene1 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	//void Render() override;

private:
	shared_ptr<class ColorCircle> playerCircle;
	shared_ptr<class CircleCollider> playerCircleCollider;
	shared_ptr<class Jump> playerCircleJump;

	shared_ptr<class ColorRect> floor;
	shared_ptr<class BoxCollider> floorCollider;

	shared_ptr<class ObjectContainer> obstacles;

	float scrollSpeed = -450.f;
	float curScrollSpeed = scrollSpeed;
};