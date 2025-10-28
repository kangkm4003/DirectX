#pragma once

class Time
{
	DECLEAR_SINGLETON(Time)

public:
	void Update();

	float GetDeltaTime() const { return (float)elapsed; }

	UINT GetFPS() const { return fps; }

	double GetWorldTime() const { return worldTime; }

	void CheckTime() const { std::cout << "FPS : " << fps << "\nDelta : " << elapsed << "\n"; }

private:
	chrono::steady_clock::time_point curTime;
	chrono::steady_clock::time_point prevTime;

	double elapsed = 0.0;

	double worldTime = 0.0;

	UINT fps = 0;

	UINT frameCount = 0;
	double fpsElapsed = 0.0;
};