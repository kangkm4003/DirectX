#include "stdafx.h"
#include "Program.h"

Program::Program()
{
	SetGlobalBuffers();
	rect.Create();
}

Program::~Program()
{
	
}

void Program::SetGlobalBuffers()
{
	{

	}
	{
		VPBuffer.SetView(XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0))); //카메라가 바라보는 위치, 방향, 위쪽 방향
		VPBuffer.SetProjection(XMMatrixOrthographicLH(gWinWidth, gWinHeight, 0, 1));
	}
}

void Program::Update()
{
	rect.Update();
}

void Program::Render()
{
	VPBuffer.SetVSBuffer(1);
	rect.Render();
}