#include "stdafx.h"
#include "Fever.h"
#include "Components/Graphic/Material.h"
#include "Utilities/Random.h"
#include "Utilities/Timer.h"

Fever::Fever(float startFeverGauge, float feveringTime, const string& name)
	: KeyMapping(name), curFeverGauge(startFeverGauge), feveringTime(feveringTime)
{
		material = GetOwner()->GetComponent<Material>("Material");
		feverColorTimer = make_unique<Timer>();
		feveringTimer = make_unique<Timer>();
}

void Fever::Update()
{
	SUPER::Update();
	if (inFever)
	{
		if (feverColorTimer->IsTimerCompleted())
		{
			material->SetColor(Random::GetColor());
			feverColorTimer->StartTimer(colorChangingTime);
		}
		if (feveringTimer->IsTimerCompleted()) //피버 종료
		{
			inFever = false;
			feverColorTimer->Pause();
			feveringTimer->Pause();
		}
	}

}

void Fever::Render()
{
	SUPER::Render();
}

void Fever::onKeyDown()
{
	if (curFeverGauge >= maxFeverGauge && material != nullptr)
	{
		inFever = true;
		curFeverGauge = 0.f;
		feverColorTimer->StartTimer(colorChangingTime);
		feveringTimer->StartTimer(feveringTime);
	}
}