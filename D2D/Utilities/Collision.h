#pragma once

class Transform;

namespace Collision
{
	struct RectData
	{
		Vector2 min;
		Vector2 max;

		RectData(Vector2 position, Vector2 scale)
		{
			Vector2 halfScale = scale * 0.5f;
			min = position - halfScale;
			max = position + halfScale;
		}


	};

	struct CircleData
	{
		Vector2 pivot;
		float radius;

		CircleData(Vector2 position, Vector2 scale)
		{
			pivot = position;
			radius = scale.x * 0.5f;
		}
	};

	bool Intersect(const RectData& rect, Vector2 point);
	bool Intersect(const CircleData& circle, Vector2 point);

	bool Collision::IntersectOBB(Transform* t1, Transform* t2);

	bool Intersect(const RectData& rect1, const RectData& rect2);
	bool Intersect(const CircleData& circle1, const CircleData& circle2);
	bool Intersect(const RectData& rect, const CircleData& circle);
	bool Intersect(const CircleData& circle, const RectData& rect);
}