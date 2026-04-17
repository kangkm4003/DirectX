#pragma
#include "Objects/Geometry/ColorCircle.h"

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
	bool isDead() const { return dead; };

	void SetImmute(float time) { immuteTime = time; };
	bool GetImmuteEnd_Dirty() const { return immuteEnd_Dirty; }
	bool isImmute();
	void ImmuteEnd();

	void AddFeverGauge(float amount) { feverGauge += amount; if (feverGauge > 100) feverGauge = 100; }
	float GetFeverGauge() const { return feverGauge; }
	bool GetInFever() const { return inFever; };
	void StartFever(float time);

	int GetMaxHealth() const { return maxHealth; }
	int GetCurHealth() const { return curHealth; }

private:
	unsigned int maxHealth = 3;
	unsigned int curHealth = maxHealth;
	float immuteTime = 0.f; //현재 남은 무적 시간
	Color origianlColor = GREEN; //무적 시간이 끝나고 돌아갈 색상
	Color damegeColor = RED; //데미지를 입었을시 바꿀 색상
	bool dead = false;

	float feverTime = 5.f; //피버의 지속시간
	float feverGauge = 0.f; //피버의 게이지 (0~100)
	float feverColorTime = 0.05f; //피버상태일시 색상이 바뀌는 속도(초)
	float feverColorTimer = 0.f; //피버상태일때 최근 색상이 바뀌고 경과한 시간
	bool inFever = false; //현재 피버 상태인지에 대한 여부

	bool immuteEnd_Dirty = false; //플레이어의 무적 상태 종료 이벤트를 종료 직후 1회만 실행하기 위한 변수값
};