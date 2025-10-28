#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	curTime = chrono::steady_clock::now();
	prevTime = curTime;
}

Time::~Time()
{

}

void Time::Update()
{
	prevTime = curTime;
	curTime = chrono::steady_clock::now();

	chrono::duration<double> delta = curTime - prevTime;
	elapsed = delta.count();

	frameCount++;
	fpsElapsed += elapsed;
	if (fpsElapsed >= 1)
	{
		fps = frameCount;
		frameCount = 0;
		fpsElapsed = 0;
		CheckTime();
	}
}