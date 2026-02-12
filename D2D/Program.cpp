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
	sceneList.push_back(make_shared<Scene2>());
	sceneList.push_back(make_shared<Scene3>());
	sceneList.push_back(make_shared<Scene4>());

	currentScene = sceneList[0];
	currentScene->Init();
}

void Program::Update()
{
	currentScene->Update();
}

void Program::Render()
{
	if(INPUT->Down(VK_F1))
	{
		SwitchScene(0);
	}
	else if (INPUT->Down(VK_F2))
	{
		SwitchScene(1);
	}
	else if (INPUT->Down(VK_F3))
	{
		SwitchScene(2);
	}
	else if (INPUT->Down(VK_F4))
	{
		SwitchScene(3);
	}

	VPBuffer->Update();
	VPBuffer->SetVSBuffer(1);

	currentScene->Render();
}

void Program::SwitchScene(int index)
{
	//너무 큰 값을 넣었을땐 바로 종료
	if (index >= sceneList.size()) return;

	if (currentScene == sceneList[index]) return;

	currentScene->Destroy();
	currentScene = sceneList[index];
	currentScene->Init();
}
