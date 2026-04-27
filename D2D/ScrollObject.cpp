#include "stdafx.h"
#include "ScrollObject.h"

//Components
#include "Components/Transform.h"

//Utilities
#include "Utilities/Random.h"


ScrollObject::ScrollObject(const string& name)
	:Component(name)
{
	transform = GetOwner()->GetTransform(); //owner의 Transform 컴포넌트 precache
}


void ScrollObject::Update()
{
	SUPER::Update();

	if (transform == nullptr) return; //Transform 컴포넌트가 없다면 위치 조정 불가능
	if (scrollSpeed.LengthSquared() < epsilon) return; //scroll 스피드가 0이라면 스크롤 불필요
	if (!doScroll) return; //스크롤 비활성화 상태라면 스크롤 불필요

	transform->SetPosition(transform->GetPosition() + Vector2(scrollSpeed.x * DELTA, scrollSpeed.y * DELTA)); //현재 위치에 스크롤 속도만큼 이동
	scrollSpeed += scrollAcceleration * DELTA; //가속도 적용

	if (doRespawnWhenOfScreen) //화면 밖으로 나갔을 때 위치 재설정이 활성화 상태라면
	{
		auto position = transform->GetPosition();
		auto scale = transform->GetScale();
		if (position.x + scale.x <= 0)
		{
			if (checkingScreenBounds[0]) //Left
				ResetPosition();
		}
		else if (position.x - scale.x >= gWinWidth)
		{
			if (checkingScreenBounds[1]) //Right
				ResetPosition();
		}

		if (position.y + scale.y <= 0)
		{
			if (checkingScreenBounds[2]) //Up
				ResetPosition();
		}
		else if (position.y - scale.y >= gWinHeight)
		{
			if (checkingScreenBounds[3]) //Down
				ResetPosition();
		}
	}
}

void ScrollObject::ResetPosition()
{
	if (transform == nullptr) return; //Transform 컴포넌트가 없다면 위치 조정 불가능
	if (reSpawnPosMin.x > reSpawnPosMax.x || reSpawnPosMin.y > reSpawnPosMax.y) return; //랜덤 위치 범위가 이상하다면 위치 조정 불가능

	if (reSpawnPosMin == reSpawnPosMax) //랜덤 위치 범위가 하나의 점이라면 Random::Range를 사용할 필요 없이 그 점으로 위치 조정
		transform->SetPosition(reSpawnPosMin);
	else
		transform->SetPosition(Vector2(Random::Range(reSpawnPosMin.x, reSpawnPosMax.x), Random::Range(reSpawnPosMin.y, reSpawnPosMax.y)));
}

