#pragma once

namespace Random
{
	void Init();

	float GetFloat();
	float Range(float min, float max);

	int Range(int min, int max);

	Color GetColor();
	Vector2 GetVector(float min, float max);
}