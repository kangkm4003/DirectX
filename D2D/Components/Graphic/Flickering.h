#pragma once
#include "Components/Component.h"

class Flickering : public Component
{
public:
	Flickering(const string& compName = "Flickering");

	void Update() override;
	void Render() override;

	//Component Precache
private:
	shared_ptr<class Material> material;
};