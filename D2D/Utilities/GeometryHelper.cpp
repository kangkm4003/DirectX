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

		}

		return mesh;
	}
}


