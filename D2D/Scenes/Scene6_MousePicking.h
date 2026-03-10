#pragma once
#include "Scene.h"

class ColorRect;

struct BoxObject
{
	shared_ptr<ColorRect> visaul;
	b2BodyId bodyId;
};

class Scene6 : public Scene
{
public:
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;

private:
	void CreateBox(Vector2 screenPos);

	b2WorldId worldId = b2_nullWorldId;

	b2BodyId groundBodyId = b2_nullBodyId;
	shared_ptr<ColorRect> groundObj;

	b2JointId mouseJointId = b2_nullJointId;

	vector<BoxObject> boxes;

	ComPtr<ID3D11RasterizerState> rs;
	ComPtr<ID3D11RasterizerState> wireframe;

	float timeScale = 1.0f;
	int subStepCount = 4;
};