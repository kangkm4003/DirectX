#pragma once
#include "_Libraries/DirectXTK/SimpleMath.h"

using namespace DirectX;
using namespace SimpleMath;

struct PhysicsState //현재 혹은 이전 프레임의 위치와 기울기를 저장
{
	Vector2 position;
	float angle = 0.0f;
};