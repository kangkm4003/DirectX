#pragma once
#include "Objects/Object.h"

class ColorCircle : public Object
{
public:
	ColorCircle(Vector2 position, Vector2 scale, Color color = RED, UINT segments = 50);
	~ColorCircle() override = default;

	void Update();
	void Render();
private:
	ComPtr<ID3D11BlendState> blendState;
};