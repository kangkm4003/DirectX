#include "stdafx.h"
#include "Transform.h"

//defines object's transform (scale rotation position)

Transform::Transform(const string& name)
	: Component(name)
{
	WB = make_unique<WorldBuffer>();
}

void Transform::Update()
{
	Matrix S = XMMatrixScalingFromVector(scale);
	Matrix R = XMMatrixRotationZ(-rotation);
	Matrix T = XMMatrixTranslationFromVector(position);

	world = S * R * T;

	WB->SetWorld(world);
	WB->Update();
}

void Transform::Render()
{
	WB->SetVSBuffer(0);
}
