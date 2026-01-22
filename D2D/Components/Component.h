#pragma once
#include "stdafx.h"
#include "Objects/Object.h"

class Component
{
public:
	Component(const string& compName) : name(compName) {}
	virtual ~Component() = default;

	virtual void Awake() {}
	virtual void Update() {}
	virtual void Render() {}

	string GetName() const { return name; }
	shared_ptr<Object> GetOwner() const { return owner; }

	void SetOwner(const shared_ptr<Object>& obj) { owner = obj; }

protected:
	string name;
	shared_ptr<Object> owner = nullptr;
};