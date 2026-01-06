#pragma once

#include "ConstantBuffer.h"

struct WorldData
{
	Matrix world;
};

class WorldBuffer : public ConstantBuffer<WorldData>
{
public:
	void SetWorld(const Matrix& matrix)
	{
		data.world = XMMatrixTranspose(matrix);
	}
};

struct VPData
{
	Matrix view;
	Matrix projection;
};

class ViewProjectionBuffer : public ConstantBuffer<VPData>
{
public:
	void SetView(const Matrix& view)
	{
		data.view = XMMatrixTranspose(view);
	}

	void SetProjection(const Matrix& projection)
	{
		data.projection = XMMatrixTranspose(projection);
	}
};

struct ColorData
{
	Color color;
};

class ColorBuffer : public ConstantBuffer<ColorData>
{
public:
	void SetColor(Color color)
	{
		data.color = color;
	}
};