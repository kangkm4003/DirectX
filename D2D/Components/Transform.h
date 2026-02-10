#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform(const string& name = "Transform");
	~Transform() override = default;

	void Update() override;
	void Render() override;

	Vector2 GetPosition() const { return position; }
	Vector2 GetScale() const { return scale; }
	float GetRotationDegree() const { return XMConvertToDegrees(rotation); }
	float GetRotationRadian() const { return rotation; }

	const Matrix& GetWorld() const { return world; }

	void SetPosition(Vector2 position)
	{
		if (this->position != position)
		{
			this->position = position;
			bDirty = true;
		}
	}

	void SetScale(Vector2 scale)
	{
		if (this->scale != scale)
		{
			this->scale = scale;
			bDirty = true;
		}
	}

	void SetRotationDegree(float degree)
	{
		float radian = XMConvertToRadians(degree);
		if (this->rotation != radian)
		{
			this->rotation = radian;
			bDirty = true;
		}
	}

	void SetRotationRadian(float radian)
	{
		if (this->rotation != radian)
		{
			this->rotation = radian;
			bDirty = true;
		}
	}

	void Move(Vector2 value)
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

	void RotateDegree(float degree)
	{
		if (abs(degree) < epsilon) return;
		float radian = XMConvertToRadians(degree);
		rotation += radian;
		bDirty = true;
	}

	void RotateRadian(float radian)
	{
		if (abs(radian) < epsilon) return;
		rotation += radian;
		bDirty = true;
	}

	Vector2 GetRight() const { return right; }
	Vector2 GetUp() const { return up; }

private:

	Vector2 right{ 1, 0 }, up{ 0, 1 };
	Vector2 position, scale{ 1, 1 };
	float rotation = 0.0f;

	Matrix world;
	unique_ptr<WorldBuffer> WB;

	bool bDirty = true;
};