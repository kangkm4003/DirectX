#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform(const string& name = "Transform");
	~Transform() override = default;

	void Update() override;
	void Render() override;

	Vector2 GetScale() const { return scale; }
	float GetRotationFromDegree() const { return XMConvertToRadians(rotation); }
	float GetRotationFromRadian() const { return rotation; }
	Vector2 GetPosition() const { return position; }

	const Matrix& GetWorld() const { return world; }

	void SetScale(Vector2 scale)
	{
		if (this->scale != scale)
		{
			this->scale = scale;
			bDirty = true;
		}
	}

	void SetRotationFromDegree(float degree)
	{
		float radian = XMConvertToRadians(degree);
		if (this->rotation != radian)
		{
			this->rotation = radian;
			bDirty = true;
		}
	}

	void SetRotationFromRadian(float radian)
	{
		if (this->rotation != radian)
		{
			this->rotation = radian;
			bDirty = true;
		}
	}

	void SetPosition(Vector2 position)
	{
		if (this->position != position)
		{
			this->position = position;
			bDirty = true;
		}
	}

	void SetRotationFromDegree(float degree)
	{
		float radian = XMConvertToRadians(degree);
		if (this->rotation != radian)
		{
			this->rotation = radian;
			bDirty = true;
		}
	}

	void SetRotationFromRadian(float radian)
	{
		if (this->rotation != radian)
		{
			this->rotation = radian;
			bDirty = true;
		}
	}

	void MovePositoin(Vector2 value)
	{
		if (value.LengthSquared() < epsilon) return;
		position += value;
		bDirty = true;
	}

	void AddScale(Vector2 value)
	{
		if (value.LengthSquared() < epsilon) return;
		scale += value;
		bDirty = true;
	}

	void AddRotateFromDegree(float degree)
	{
		if (abs(degree) < epsilon) return;
		float radian = XMConvertToRadians(degree);
		rotation += radian;
		bDirty = true;
	}

	void AddRotateFromRadian(float radian)
	{
		if (abs(radian) < epsilon) return;
		rotation += radian;
		bDirty = true;
	}

private:
	Vector2 position, scale{ 1, 1 };
	float rotation = 0.0f;

	Matrix world;
	unique_ptr<WorldBuffer> WB;

	bool bDirty = true;
};