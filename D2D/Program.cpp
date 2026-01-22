#include "stdafx.h"
#include "Program.h"
#include "Objects/ColorRect.h"
#include "Objects/Circle.h"
#include "Objects/SolidCircle.h"
#include "Objects/Line.h"

Program::Program()
{
	VPBuffer = make_unique<ViewProjectionBuffer>();

	SetGlobalBuffers();

	//rect = make_unique<ColorRect>(CENTER, Vector2(100, 100), 20.0f, BLUE);
	line = make_unique<Line>(CENTER, Vector2(200, 200), 0);
}

Program::~Program()
{

}

void Program::SetGlobalBuffers()
{
	view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	projection = XMMatrixOrthographicOffCenterLH(0, gWinWidth, 0, gWinHeight, 0, 1);

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);
}

void Program::Update()
{
	line->Update();
}

void Program::Render()
{
	VPBuffer->Update();
	VPBuffer->SetVSBuffer(1);

	line->Render();
}
