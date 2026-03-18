#pragma
#include "ColorCircle.h"

class PlayerCircle : public ColorCircle
{
public:
	PlayerCircle(Vector2 position, Vector2 scale, Color color = RED, UINT segments = 50);
	~PlayerCircle() override = default;

	void Update();
	void Render();

	void Damege(int damege, float immute_time);
	void Heal(int amount);
	void Dead();

	void setImmute(float time) { immuteTime = time; };
	bool isImmute();
	bool isDead() { return dead; };

	int getMaxHealth() { return maxHealth; }
	int getCurHealth() { return curHealth; }

private:
	unsigned int maxHealth = 3;
	unsigned int curHealth = maxHealth;
	float immuteTime = 0.f; //현재 남은 무적 시간
	bool dead = false;
};