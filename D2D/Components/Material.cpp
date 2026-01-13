#include "stdafx.h"
#include "Material.h"

Material::Material(Color color, UINT slot, const string& compName)
	: Component(compName) {
	CB = make_unique<ColorBuffer>();
	SetColor(color);
}

void Material::Render()
{
	CB->SetPSBuffer(slot);
}
