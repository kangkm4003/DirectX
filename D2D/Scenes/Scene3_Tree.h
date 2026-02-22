#pragma once
#include "Scene.h"

class ColorRect;
class ObjectGroup;

class Scene3 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	//void Render() override;

private:

	shared_ptr<ObjectGroup> TreeObject_Group;
	shared_ptr<ObjectGroup> Star_Group;
	//멤버가 많지 않기에 star 오브젝트들 캐싱 
	shared_ptr<Transform> starRect1_tr;
	shared_ptr<Transform> starRect2_tr;
	shared_ptr<Transform> starCircle_tr;
	//
	//별들 크기 커졌다 작아졌다 하는거
	float defaultScale; //기본 크기. starRect1의 X크기를 기준으로 함
	float scaleAmount = 20; //크기변화의 강도
	float rotateSpeed = 5; //변화할 속도
	//

	shared_ptr<ObjectGroup> Gift1_Group;
	shared_ptr<ObjectGroup> Gift2_Group;

};