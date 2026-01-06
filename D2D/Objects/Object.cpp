#include "stdafx.h"
#include "Object.h"
#include "Components/Component.h"
#include "Components/Transform.h"

Object::Object(const string& name, Vector2 position, Vector2 scale, float rotation)
	: name(name)
{
	transform = make_shared<Transform>();

	transform->SetScale(scale);
	transform->SetRotationDegree(rotation);
	transform->SetPosition(position);

	AddComponent(transform);
}

void Object::AddComponent(const shared_ptr<Component>& component)
{
	const auto& result = components.try_emplace(component->GetName(), component);

	if (result.second)
	{
		component->SetOwner(this);
		components_Update_Order.push_back(component);
	}
}

void Object::Awake()
{
	for (const auto& comp : components_Update_Order)
		comp->Awake();

}

void Object::Update()
{
	for (const auto& comp : components_Update_Order)
		comp->Update();

	transform->Update();
}

void Object::Render()
{
	for (const auto& comp : components_Update_Order)
		comp->Render();

	transform->Render();
}