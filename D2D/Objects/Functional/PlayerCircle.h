#pragma
#include "Objects/Geometry/ColorCircle.h"

//ToDo : Jump와 Controlloer 컴포넌트 구현 (컴포넌트에서 키를 누르면 owner에게 신호 전달하는 형태)
class PlayerCircle : public ColorCircle
{
public:
	PlayerCircle(Vector2 position, Vector2 scale, Color color = RED, UINT segments = 50);
	~PlayerCircle() override = default;

	void Update();
	void Render();

	void AddFeverGauge(float amount) { feverGauge += amount; if (feverGauge > 100) feverGauge = 100; }
	float GetFeverGauge() const { return feverGauge; }
	bool GetInFever() const { return inFever; };
	void StartFever(float time);

private:

	float feverTime = 5.f; //피버의 지속시간
	float feverGauge = 0.f; //피버의 게이지 (0~100)
	float feverColorTime = 0.05f; //피버상태일시 색상이 바뀌는 속도(초)
	float feverColorTimer = 0.f; //피버상태일때 최근 색상이 바뀌고 경과한 시간
	bool inFever = false; //현재 피버 상태인지에 대한 여부

	bool immuteEnd_Dirty = false; //플레이어의 무적 상태 종료 이벤트를 종료 직후 1회만 실행하기 위한 변수값
};