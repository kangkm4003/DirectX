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
	shared_ptr<ObjectGroup> Gift1_Group;
	shared_ptr<ObjectGroup> Gift2_Group;

};