#include "stdafx.h"
#include "Timer.h"

Timer::Timer(float timerRate)
	: timeRate(timerRate)
{
	if (timeRate < 0.f)
		timeRate *= -timeRate; //만약 timerRate를 음수로 설정했다면 값 반전으로 양수로 변경
}

void Timer::Update()
{
	if (paused || completed) return;

	if (curTimer > epsilon)
		curTimer -= DELTA * timeRate;
	else if (curTimer < epsilon) //타이머 종료
	{
		//if (endFunc) endFunc(); //타이머 종료 함수 호출 
		curTimer = 0.f;
		completed = true;
		//if (curLoops != -1) //타이머가 무한 반복이 아니라면 루프 횟수 1회 차감
		//	curLoops -= 1;
		//if (curLoops > 0 || curLoops == -1) //curLoops의 값이 0보다 크다면 타이머 다시 실행. curLoops가 -1 이라면 타이머 무한 반복
		//{
		//	curTimer = startTimer;
		//}
	}
}

void Timer::StartTimer(float value)
{
	if (value > 0) startTimer = value;
	else if (value == 0) startTimer = 1; //loops 값을 0으로 잘못 입력 했을시에 대한 안전장치
	curTimer = value;
	//curLoops = loops;
	paused = false;
	completed = false;
}

void Timer::Stop() //멤버값 초기화로 타이머 종료
{
	paused = true;
	startTimer = 0.f;
	curTimer = 0.f;
	//curLoops = 0.f;
}
