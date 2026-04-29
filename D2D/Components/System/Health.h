#pragma once
#include "Components/Component.h"

class Health : public Component
{
public:
	Health(unsigned int maxHealth, const string& name = "Health") : Component(name), maxHealth(maxHealth) {}

	void Update() override;

	void Damege(int damege, float immute_time);
	void Heal(int amount);
	void Dead();
	bool isDead() const { return dead; }

	int GetMaxHealth() const { return maxHealth; }
	int GetCurHealth() const { return curHealth; }

	void SetImmute(float time) { immuteTime = time; };
	bool GetImmuteEnd_Dirty() const { return immuteEnd_Dirty; }
	bool isImmute();
	void ImmuteEnd();
//Variables
private:
	unsigned int maxHealth = 3;
	unsigned int curHealth = maxHealth;
	bool dead = false;

	float immuteTime = 0.f; //현재 남은 무적 시간
	Color origianlColor = GREEN; //무적 시간이 끝나고 돌아갈 색상
	Color damegeColor = RED; //데미지를 입었을시 바꿀 색상

	bool immuteEnd_Dirty = false; //플레이어의 무적 상태 종료 이벤트를 종료 직후 1회만 실행하기 위한 변수값
}