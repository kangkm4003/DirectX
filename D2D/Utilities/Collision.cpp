#include "stdafx.h"
#include "Collision.h"
#include "Objects/Object.h"
#include "Components/Transform.h"

bool Collision::Intersect(const RectData& rect, Vector2 point)
{
	return (rect.min.x <= point.x && point.x <= rect.max.x &&
		rect.min.y <= point.y && point.y <= rect.max.y);
}

bool Collision::Intersect(const CircleData& circle, Vector2 point)
{
	const float distanceSq = Vector2::DistanceSquared(point, circle.pivot);
	return distanceSq <= circle.radius * circle.radius;
}

bool Collision::Intersect(const RectData& rect1, const RectData& rect2)
{
	return (rect1.min.x <= rect2.max.x && rect2.min.x <= rect1.max.x &&
		rect1.min.y <= rect2.max.y && rect2.min.y <= rect1.max.y);
}

bool Collision::Intersect(const CircleData& circle1, const CircleData& circle2)
{
	const float distanceSq = Vector2::DistanceSquared(circle1.pivot, circle2.pivot);
	return distanceSq <= (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);
}

bool Collision::Intersect(const RectData& rect, const CircleData& circle)
{
	Vector2 closest; // 원의 중심에서 가장 가까운 사각형 위의 점.

	closest.x = max(rect.min.x, min(circle.pivot.x, rect.max.x));
	closest.x = max(rect.min.y, min(circle.pivot.y, rect.max.y));

	const float distanceSq = Vector2::DistanceSquared(closest, circle.pivot);

	return distanceSq <= circle.radius * circle.radius;
}

bool Collision::Intersect(const CircleData& circle, const RectData& rect)
{
	Vector2 closest; // 원의 중심에서 가장 가까운 사각형 위의 점.

	closest.x = max(rect.min.x, min(circle.pivot.x, rect.max.x));
	closest.x = max(rect.min.y, min(circle.pivot.y, rect.max.y));

	const float distanceSq = Vector2::DistanceSquared(closest, circle.pivot);

	return distanceSq <= circle.radius * circle.radius;
}

bool IntersectOBB(const Transform* t1, const Transform* t2)
{
	const float distance = Vector2::Distance(t1->GetPosition(), t2->GetPosition());
	const float X_axis = abs(t1->GetPosition().x - t2->GetPosition().x);

	return false;
}
