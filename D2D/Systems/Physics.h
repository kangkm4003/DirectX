#pragma once

class Physics
{
	DECLARE_SINGLETON(Physics)

public:
	void Init();
	void Destroy();
	void Update();

	b2WorldId GetWorldId() const { return worldId; }

private:
	b2WorldId worldId = b2_nullWorldId;
	float timeScale = 1.f;
	int subStepCount = 4;

	float stepSize = 1.f / 60.f;
	float accumulator = 0;
};