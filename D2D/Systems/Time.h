#pragma once

class Time
{
	DECLARE_SINGLETON(Time)

public:
	void Update();

	float GetDeltaTime() const { return (float)deltaTime; }
	UINT GetFPS() const { return fps; }
	double GetWorldTime() const { return worldTime; }

	void CheckTime() const { cout << "FPS : " << fps << ", DeltaTime : "
		<< deltaTime << ", WorldTime : " << worldTime << '\n'; }

private:
	chrono::steady_clock::time_point currentTime;
	chrono::steady_clock::time_point lastTime;

	double deltaTime = 0.0;

	double worldTime = 0.0;
	UINT fps = 0;

	UINT frameCount = 0;
	double fpsTimeElapsed = 0.0;
};