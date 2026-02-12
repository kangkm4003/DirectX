#include "stdafx.h"
#include "Collision.h"
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

bool Collision::IntersectOBB(const shared_ptr<Transform>& t1, const shared_ptr<Transform>& t2)
{
	//서로의 중심점 기준의 거리
	const Vector2 dist = t1->GetPosition() - t2->GetPosition();

	//각각의 up 벡터와 right 벡터를 배열로 저장
	const Vector2 axes[] = { t1->GetRight(), t1->GetUp(), t2->GetRight(), t2->GetUp() };

	//t1과 t2의 반지름 벡터 (길이)
	const Vector2 t1ArmW = axes[0] * (t1->GetScale().x * 0.5f);
	const Vector2 t1ArmH = axes[1] * (t1->GetScale().y * 0.5f);
	const Vector2 t2ArmW = axes[2] * (t2->GetScale().x * 0.5f);
	const Vector2 t2ArmH = axes[3] * (t2->GetScale().y * 0.5f);

	for (auto axis : axes)
	{
		//서로의 중심점간의 거리벡터를 축에 투영한 길이(내적)
		const float projDist = abs(dist.Dot(axis));

		//각각의 반지름 벡터의 내적한 값
		const float r1 = abs(t1ArmW.Dot(axis)) + abs(t1ArmH.Dot(axis));
		const float r2 = abs(t2ArmW.Dot(axis)) + abs(t2ArmH.Dot(axis));

		//값을 더했을때 중점끼리의 거리값 보다 작다면 false)
		if (projDist > r1 + r2) return false;
	}
	//모든 정점의 길이가 거리값보다 크다면 true)
	return true;
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
	closest.y = max(rect.min.y, min(circle.pivot.y, rect.max.y));

	const float distanceSq = Vector2::DistanceSquared(closest, circle.pivot);

	return distanceSq <= circle.radius * circle.radius;
}

bool Collision::Intersect(const CircleData& circle, const RectData& rect)
{
	Vector2 closest; // 원의 중심에서 가장 가까운 사각형 위의 점.

	closest.x = max(rect.min.x, min(circle.pivot.x, rect.max.x));
	closest.y = max(rect.min.y, min(circle.pivot.y, rect.max.y));

	const float distanceSq = Vector2::DistanceSquared(closest, circle.pivot);

	return distanceSq <= circle.radius * circle.radius;
}