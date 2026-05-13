#include "stdafx.h"
#include "Fever.h"
#include "Components/Graphic/Material.h"
#include "Components/Graphic/MeshRenderer.h"
#include "Components/System/Health.h"
#include "Utilities/Random.h"
#include "Utilities/Timer.h"
#include "Utilities/GeometryHelper.h"

Fever::Fever(float startFeverGauge, float feveringTime, const string& name)
	: KeyMapping(name), curFeverGauge(startFeverGauge), feveringTime(feveringTime)
{
		material = GetOwner()->GetComponent<Material>("Material");
		meshRenderer = GetOwner()->GetComponent<MeshRenderer>("MeshRenderer");
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
			feverColorTimer->Start(colorChangingTime);
		}
		if (feveringTimer->IsTimerCompleted()) //피버 종료
		{
			inFever = false;
			feverColorTimer->Stop();
			feveringTimer->Stop();
		}
	}

}
void Fever::onKeyDown()
{
	if (curFeverGauge >= maxFeverGauge && material != nullptr)
	{
		meshRenderer->SetMesh(GeometryHelper::CreateRectangle());
		inFever = true;
		curFeverGauge = 0.f;
		feverColorTimer->Start(colorChangingTime);
		feveringTimer->Start(feveringTime);
		health->SetImmute(feveringTime);
	}
}