#include "stdafx.h"
#include "GeometryHelper.h"
#include "Renders/Resources/Mesh.h"

namespace GeometryHelper
{
	shared_ptr<Mesh> CreateRectangle()
	{
		static shared_ptr<Mesh> mesh = nullptr;

		if (mesh == nullptr)
		{
			vector<Vertex> vertices(4);
			vertices[0].position = Vector2(-0.5f, -0.5f);
			vertices[1].position = Vector2(-0.5f, 0.5f);
			vertices[2].position = Vector2(0.5f, -0.5f);
			vertices[3].position = Vector2(0.5f, 0.5f);

			vector<UINT> indices = { 0, 1, 2, 2, 1, 3 };

			mesh = make_shared<Mesh>();
			mesh->Create(vertices, indices);
		}

		return mesh;
	}

	shared_ptr<Mesh> CreateColorCircle(UINT quality)
	{
		static shared_ptr<Mesh> mesh = nullptr;
		if (mesh == nullptr || quality != 0 || quality == NULL)
		{
			if (quality > 3)
				return;

			FLOAT theta = 2 * XM_PI / quality;
			vector<Vertex> vertices(quality);
			vector<UINT> indices(quality);

			for (UINT i = 1; i < quality; i * 3)
			{
				vertices[i].position = Vector2((sinf(theta / i), cosf(theta / i)));

				indices[i] = 0;
					
			}

			mesh = make_shared<Mesh>();
			mesh->Create(vertices, indices);

		}

		return mesh;
	}
	shared_ptr<Mesh> CreateSolidColorCircle(UINT quality)
	{
		return shared_ptr<Mesh>();
	}
}
