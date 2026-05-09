#include "stdafx.h"
#include "Flickering.h"

Flickering::Flickering(const string& compName)
	: Component(compName)
{
	material = GetOwner()->GetComponent<Material>("Material");
}

void Flickering::Update()
{
	SUPER::Update();
}

void Flickering::Render()
{
	SUPER::Update();

}
