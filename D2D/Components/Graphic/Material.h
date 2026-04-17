#pragma once
#include "Components/Component.h"

class Material : public Component
{
public:
	Material(Color color, UINT slot, const string& compName = "Material");

	Color GetColor() const { return color; }

	void Render() override;

	void SetColor(Color color)
	{
		if (this->color == color) return;

		this->color = color;
		CB->SetColor(color);
		CB->Update();
	}

private:
	unique_ptr<ColorBuffer> CB;

	UINT slot = 0;

	Color color;
};