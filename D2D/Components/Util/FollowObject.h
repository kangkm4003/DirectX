#pragma once
#include "Components/Component.h"

//TransForm Component required to use this
class FollowObject : public Component
{
public:
	FollowObject(int followPosition = 0x11, int followScale = 0x11, bool followRotation = true, float delayTime = 0.0f, const string& name = "FollowObject");

	void Update() override;

	void doFollowWith(shared_ptr<Transform> target);
	void stopFollowing() { followingObject = nullptr; };

	int followPosition = 0x11; /*어떤 위치좌표를 따라갈지
	0x10 : X 좌표만 
	0x01 : Y 좌표만
	0x11 : 둘다
	0x00 : 없음. 비활성화
	*/
	int followScale = 0x11; //위와 같음. 대신 Scale값을 따라감

	bool followRotation = true; //rotation값을 따라갈지

private:
	float followDelayTime = 0.f; //현재 미구현
	shared_ptr<Transform> followingObject = nullptr; //따라갈 오브젝트의 transform
	shared_ptr<Transform> ownerTransform = nullptr; //컴포넌트 owner의 transform
};
