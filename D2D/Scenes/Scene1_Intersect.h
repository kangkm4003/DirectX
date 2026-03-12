#pragma once
#include "Scene.h"

class ColorRect;
class ColorCircle;
class BoxCollider;
class CircleCollider;
class WireCircle;

class Scene1 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	//void Render() override;

private:

	//멤버로 오브젝트를 선언했다면 destroy에서 nullptr로 해야 한다.
	shared_ptr <ColorRect> rect1;
	shared_ptr<BoxCollider> rect1HitBox;

	shared_ptr<ColorRect> rect2;
	shared_ptr<BoxCollider> rect2HitBox;

	shared_ptr<ColorCircle> circle1;
	shared_ptr<CircleCollider> circle1HitBox;

	shared_ptr<WireCircle> circle2;
	shared_ptr<CircleCollider> circle2HitBox;
};