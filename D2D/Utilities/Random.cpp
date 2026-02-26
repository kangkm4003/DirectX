#include "stdafx.h"
#include "Random.h"
#include <random>

namespace
{
	random_device rd;
	mt19937 gen;
}

namespace Random
{
	void Init()
	{
		gen.seed(rd());
	}

	float GetFloat()
	{
		static uniform_real_distribution<float> dis(0.0f, 1.0f);
		return dis(gen);
	}

	float Range(float min, float max)
	{
		uniform_real_distribution<float> dis(min, max);
		return dis(gen);
	}

	int Range(int min, int max)
	{
		uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}

	Color GetColor()
	{
		return Color(GetFloat(), GetFloat(), GetFloat());
	}

	Vector2 GetVector(float min, float max)
	{
		return Vector2(Range(min, max), Range(min, max));
	}
}