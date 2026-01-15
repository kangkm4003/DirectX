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
		if (mesh == nullptr)
		{

			FLOAT theta = 2 * XM_PI / quality;
			vector<Vertex> vertices(quality + 1); //인덱스 0번은 원의 중점
			vector<UINT> indices(quality * 3); // 삼각형을 quality만큼 그린다
			vertices[0].position = Vector2(0.f, 0.f);
			for (UINT i = 1; i < quality + 1; i++)
			{
				vertices[i].position = Vector2((sinf(theta * (i - 1)), cosf(theta * (i - 1)))) * 0.5; //로컬좌표를 -1 ~ 1 까지로 축소

				indices.push_back(0);
				indices.push_back(i);
				indices.push_back(i+1);
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
