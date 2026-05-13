#include "stdafx.h"
#include "Flickering.h"

#include "Components/Graphic/Material.h"

#include "Utilities/Timer.h"

Flickering::Flickering(const string& compName)
	: Component(compName)
{
	material = GetOwner()->GetComponent<Material>("Material");
	timer = make_unique<Timer>();
}

void Flickering::Update()
{
	SUPER::Update();
	if (timer->IsTimerCompleted())
	{
		Color color = material->GetColor();
		material->SetColor(Color(color[0], color[1], color[2], !color[3])); //alpha 값 반전
		timer->Start(time);
	}
}

void Flickering::Render()
{
	SUPER::Update();
}

void Flickering::Start()
{
	timer->Start(time);
}

void Flickering::Stop()
{
	timer->Stop();
}
