#include "stdafx.h"
#include "Program.h"
#include "Scenes/SceneList.h"

Program::Program()
{
	VPBuffer = make_unique<ViewProjectionBuffer>();

	SetGlobalBuffers();
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

void Program::Init()
{
	sceneList.push_back(make_shared<Scene1>());

	currentScene = sceneList[0];
	currentScene->Init();
}

void Program::Update()
{
	currentScene->Update();
}

void Program::Render()
{
	VPBuffer->Update();
	VPBuffer->SetVSBuffer(1);

	currentScene->Render();
}
