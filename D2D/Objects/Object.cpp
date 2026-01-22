#include "stdafx.h"
#include "Object.h"
#include "Components/Component.h"
#include "Components/Transform.h"

Object::Object(const string& name, Vector2 position, Vector2 scale, float rotation)
	: name(name)
{
	transform = make_shared<Transform>();

	transform->SetPosition(position);
	transform->SetScale(scale);
	transform->SetRotationDegree(rotation);

	AddComponent(transform);
}

void Object::AddComponent(const shared_ptr<Component>& component)
{
	const auto& result = components.try_emplace(component->GetName(), component);

	if (result.second)
	{
		component->SetOwner(shared_from_this());
		if (component != transform)
			updateList.push_back(component);
	}
}

void Object::Awake()
{
	for (const auto& comp : updateList)
		comp->Awake();
}

void Object::Update()
{
	for (const auto& comp : updateList)
		comp->Update();

	transform->Update();
}

void Object::Render()
{
	transform->Render();

	for (const auto& comp : updateList)
		comp->Render();
}