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
	void startFever(float duration);

	bool isImmute();
	bool isFever();
	bool isDead() { return dead; };
	void addFeverGauge(float amount) { feverGauge += amount; if (feverGauge > 100) feverGauge = 100; }

	int getMaxHealth() { return maxHealth; }
	int getCurHealth() { return curHealth; }
	float getFeverGauge() { return feverGauge; }

private:
	unsigned int maxHealth = 3;
	unsigned int curHealth = maxHealth;
	float immuteTime = 1.5f; //데미지를 입었을때에 무적 시간
	float feverTime = 5.f; //피버의 지속시간
	float feverGauge = 100.f; //피버의 게이지 (0~100)
	bool inFever = false;
	bool dead = false;
	Color original_color = RED; //무적시간 종료시 원래 색으로 돌아가기 위해 값 저장
};