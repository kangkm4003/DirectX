#pragma once
#include "Components/Component.h"

class Timer
{
public:
	Timer(float timeRate = 1.f);
	~Timer() {}

	void Update();

	void StartTimer(float value = 1.f);

	void Pause() { paused = true; } //타이머 일시정지
	void Resume() { paused = false; } //타이머 일시정지 해제
	void Stop(); //타이머 강제 종료 (무한 반복 타이머라면 더이상 반복하지 않음)
	bool IsTimerCompleted() { return completed; }
	
	float timeRate = 1.f; //타이머의 시간이 줄어드는 속도값 (1.f = 현실시간 1초)
	//void (*endFunc)(); //타이머 종료시 실행할 함수의 주소값 (구현 실패)

private:
	bool completed = false; //타이머 가 0에 도달했는지 여부
	bool paused = true;
	float startTimer = 0.f; //타이머가 한번 루프하고 돌아갈 값
	float curTimer = 0.f; //현재 타이머의 남은 시간
	//int curLoops = 0.f; //타이머의 남은 루프 횟수
};
