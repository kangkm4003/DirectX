#pragma once

class Component;
class Transform;

class Object
{
public:
	Object(const string& name, Vector2 position, Vector2 scale = { 1, 1 }, float rotation = 0.0f);
	virtual ~Object() = default;

	void AddComponent(const shared_ptr<Component>& component);

	template<typename T>
	shared_ptr<T> GetComponent(const string& compName) const
	{
		auto it = components.find(compName);
		if (it != components.end())
			return dynamic_pointer_cast<T>(it->second);
		return nullptr;
	}

	shared_ptr<Transform> GetTransFrom() { return transform; }

	virtual void Awake();
	virtual void Update();
	virtual void Render();

protected:
	string name = "";

	shared_ptr<Transform> transform;
	unordered_map<string, shared_ptr<Component>> components;
	vector<shared_ptr<Component>> components_Update_Order;
};