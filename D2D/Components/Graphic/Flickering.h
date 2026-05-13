#pragma once
#include "Components/Component.h"

class Flickering : public Component
{
public:
	Flickering(const string& compName = "Flickering");

	void Update() override;
	void Render() override;

	void Start();
	void Stop();

	float time = 0.1f; //깜빡이는 속도 (N초마다 투명화와 복귀를 반복)

private:
	unique_ptr<class Timer> timer;

	//Component Precache
private:
	shared_ptr<class Material> material;
};