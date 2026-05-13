#pragma once
#include "Components/Input/KeyMapping.h"

class Jump : public KeyMapping
{
public:
	Jump(float jumpAmount = 10.f, float gravity = 2000.f, const string& name = "Jump");

	void Update() override;

	
	void SetSpeed(float amount) { speed = amount; }
	float GetSpeed() { return speed; }

	bool GetOnAir() const { return onAir; }

	float jumpAmount = 800.f;
	float gravity = 2000.f;
	int maxJumpCount = 1; //최대 공중 점프 횟수
	int curJumpCount = 0; //현재 공중 점프 횟수
	void Land(shared_ptr<Transform> platform); //바닥에 착지함 speed 초기화
protected:
	void onKeyDown() override;

private:
	bool onAir = true; //현재 공중에 뜬 상태인지
	shared_ptr<Transform> transform;
	void DoJump(float amount); //점프
	float speed = 0.f; // owner가 매 Update마다 이동할 거리(DELTA 미적용)
};