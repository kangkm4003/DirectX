#include "stdafx.h"
#include "Object.h"
#include "Components/Component.h"

Object::Object(const string& name, Vector2 position, Vector2 scale, float rotation)
	: name(name), position(position), scale(scale), rotation(rotation)
{
	WB = make_unique<WorldBuffer>();
}

void Object::AddComponent(const shared_ptr<Component>& component)
{
	const auto& result = components.try_emplace(component->GetName(), component);

	if (result.second)
	{
		component->SetOwner(this);
	}
}

void Object::Awake()
{
	for (const auto& comp : components)
		comp.second->Awake();
}

void Object::Update()
{
	for (const auto& comp : components)
		comp.second->Update();

	Matrix S = XMMatrixScalingFromVector(scale);
	Matrix R = XMMatrixRotationZ(-rotation);
	Matrix T = XMMatrixTranslationFromVector(position);

	world = S * R * T;

	WB->SetWorld(world);
	WB->Update();
}

void Object::Render()
{
	for (const auto& comp : components)
		comp.second->Render();

	WB->SetVSBuffer(0);
}