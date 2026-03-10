#pragma once
#include <cstdint>
#include <box2d/box2d.h>
#include "_Libraries/DirectXTK/SimpleMath.h"

constexpr float Pixel_to_Meter_RATIO = 50.0f;

namespace PhysicsUtils //픽셀 <-> 미터 단위 변환
{
	inline float PixelsToMeters(float pixels)
	{
		return pixels / Pixel_to_Meter_RATIO;
	}
	inline float MetersToPixels(float meters)
	{
		return meters * Pixel_to_Meter_RATIO;
	}
	inline b2Vec2 PixelsToMeters(DirectX::SimpleMath::Vector2 pixels)
	{
		return b2Vec2{ pixels.x / Pixel_to_Meter_RATIO, pixels.y / Pixel_to_Meter_RATIO };
	}
	inline DirectX::SimpleMath::Vector2 MetersToPixels(b2Vec2 meters)
	{
		return DirectX::SimpleMath::Vector2{ meters.x * Pixel_to_Meter_RATIO, meters.y * Pixel_to_Meter_RATIO };
	}
}