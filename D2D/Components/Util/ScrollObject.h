#pragma once
#include "Components/Component.h"

//TransForm Component required to use this
class ScrollObject : public Component
{
public:
	ScrollObject(const string& name = "ScrollObject");

	void Update() override;

	bool doScroll = true; //스크롤 활성화 여부. false라면 scrollSpeed와 scrollAcceleration이 0이 아니더라도 스크롤하지 않음.
	Vector2 scrollSpeed = Vector2( //스크롤 속도. 단위는 픽셀/초
		0, //X
		0 //Y
	);
	Vector2 scrollAcceleration = Vector2(); //스크롤 가속도.

	bool doRespawnWhenOfScreen = true; //스크롤이 화면 밖으로 나갔을 때 위치 재설정 여부. true라면 reSpawnPosMin과 reSpawnPosMax를 기준으로 랜덤한 위치에 스폰
	Vector2 reSpawnPosMin = Vector2(); //위치 재설정 시 랜덤한 위치의 최소값
	Vector2 reSpawnPosMax = Vector2(); //위치 재설정 시 랜덤한 위치의 최대값

	vector<bool> checkingScreenBounds = { //화면의 어느 방향으로 나갔을때 위치 재설정 여부.
		false, //Left
		false, //Right
		false, //Up
		false  //Down
	};
private:
	void ResetPosition(); //화면 밖으로 나갔을 때 위치 재설정하는 함수

	//Component Precache
	shared_ptr<Transform> transform = nullptr;
};
