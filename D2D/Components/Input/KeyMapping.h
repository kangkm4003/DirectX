#pragma once
#include "Components/Component.h"

class KeyMapping : public Component
{
public:
	KeyMapping(const string& name = "KeyMapping")
		: Component(name) 
	{
	}

	void Update() override;
	void Render() override;

	void SetMappingKey(int key) { curMappedKey = key; }
	int GetMappingKey() { return curMappedKey; }


protected:
	virtual void onKeyDown() {}
	virtual void onKeyUp() {}
	virtual void onKeyPress() {}
	unsigned int curMappedKey;
};
