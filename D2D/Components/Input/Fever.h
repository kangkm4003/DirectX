#pragma once
#include "Components/Input/KeyMapping.h"
#include "Utilities/Timer.h"

class Fever : public KeyMapping
{
public:
	Fever(float startFeverGauge = 0.f, float feveringTime = 10.f, const string& name = "Fever");

	void Update() override;

	void SetFeveringTime(float value) { feveringTime = value; }
	bool GetinFever() const { return inFever; }

protected:
	void onKeyDown() override;

private:
	float colorChangingTime = 0.1f; //N초 마다 색상 변경
	float feveringTime = 10.f; //피버 유지 시간
	unique_ptr<Timer> feverColorTimer;
	unique_ptr<Timer> feveringTimer;
	void ChangeColor()
	{
		material;
	}
	bool inFever = false; //현재 피버 상태인지에 대한 여부

	float minFeverGauge = 0.f;
	float curFeverGauge = minFeverGauge;
	float maxFeverGauge = 100.f;

	//Component Precache
private:
	shared_ptr<class Material> material;
	shared_ptr<class MeshRenderer> meshRenderer;
	shared_ptr<class Health> health;
};