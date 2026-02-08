#include "stdafx.h"
#include "Transform.h"

Transform::Transform(const string& name)
	: Component(name)
{
	WB = make_unique<WorldBuffer>();
}

void Transform::Update()
{
	if (bDirty == false) return;

	float s, c;
	XMScalarSinCos(&s, &c, -rotation);
	right = Vector2(c, s);
	up = Vector2(-s, c);

	Matrix S = XMMatrixScalingFromVector(scale);
	Matrix R = XMMatrixRotationZ(-rotation);
	Matrix T = XMMatrixTranslationFromVector(position);

	world = S * R * T;

	WB->SetWorld(world);
	WB->Update();

	bDirty = false;
}

void Transform::Render()
{
	WB->SetVSBuffer(0);
}
