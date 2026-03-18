#pragma once
#include "Component.h"

class Jump : public Component
{
public:
	Jump(float speed = 10.f, float gravity = 10.f, const string& name = "Jump")
		: Component(name)
	{
	}

	void Update() override;

	void doJump(float amount); //점프
	void Land(); //바닥에 착지함 speed 초기화

	void SetMaxJumpCount(int count) { if (count >= 1) maxJumpCount = count; }
	void SetGravity(float amount) { if (amount >= 0) gravity = amount; }
	bool GetonAir() { return onAir; }
	void SetonAir(bool boolean) { onAir = boolean; }
	float GetSpeed() { return speed; }
private:
	float gravity = 20.f;
	int maxJumpCount = 1; //최대 공중 점프 횟수
	int curJumpCount = 0; //현재 공중 점프 횟수
	bool onAir = true; //현재 공중에 뜬 상태인지
	float speed = 0.f; // owner가 매 Update마다 이동할 거리(DELTA 미적용)
};