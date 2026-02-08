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
		static unordered_map<UINT, shared_ptr<Mesh>> cache;

		if (cache.count(quality) > 0)
			return cache[quality];

		vector<Vertex> vertices(quality + 1);
		vertices[0].position = Vector2();

		for (UINT i = 1; i <= quality; ++i)
		{
			float theta = 2.0f * XM_PI * (i - 1) / quality;
			vertices[i].position = Vector2(sinf(theta), cosf(theta)) * 0.5f;
		}

		vector<UINT> indices;
		indices.reserve(quality * 3);
		for (UINT i = 0; i < quality; ++i)
		{
			indices.push_back(0);
			indices.push_back(i + 1);
			//indices.push_back(i + 2);
			indices.push_back((i + 2 > quality) ? 1 : i + 2);
		}

		auto mesh = make_shared<Mesh>();
		mesh->Create(vertices, indices);

		cache[quality] = mesh;

		return mesh;
	}

shared_ptr<Mesh> CreateWireCircle(UINT quality)
	{
		static unordered_map<UINT, shared_ptr<Mesh>> cache;

		if (cache.count(quality) > 0)
			return cache[quality];

		vector<Vertex> vertices(quality);
		for (UINT i = 0; i < quality; ++i)
		{
			float theta = 2.0f * XM_PI * i / quality;
			vertices[i].position = Vector2(sinf(theta), cosf(theta)) * 0.5f;
		}

		vector<UINT> indices;
		indices.reserve(quality + 1);
		for (UINT i = 0; i < quality; ++i)
			indices.push_back(i);

		indices.push_back(0);

		auto mesh = make_shared<Mesh>();
		mesh->Create(vertices, indices);

		cache[quality] = mesh;

		return mesh;
	}

shared_ptr<Mesh> CreateLine()
	{
		static shared_ptr<Mesh> mesh = nullptr;
		if (mesh == nullptr)
		{

			vector<Vertex> vertices(2);
			vertices[0].position = Vector2(0.f, -0.5f);
			vertices[1].position = Vector2(0.f, 0.5f);

			vector<UINT> indices = { 0, 1};

			mesh = make_shared<Mesh>();
			mesh->Create(vertices, indices);

		}

		return mesh;
	}
}
