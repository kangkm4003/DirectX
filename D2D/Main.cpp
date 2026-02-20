#include "stdafx.h"
#include "Systems/Window.h"

HWND gHandle = nullptr;
float gWinWidth = WIN_DEFAULT_WIDTH;
float gWinHeight = WIN_DEFAULT_HEIGHT;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	WinDesc desc;
	desc.appName = L"D2D";
	desc.instance = hInstance;
	desc.handle = nullptr;
	desc.width = gWinWidth;
	desc.height = gWinHeight;

	auto window = make_unique<Window>(desc);

	WPARAM wParam = window->Run();

	return int(wParam);
}

//ToDo: 크리스마스 트리 완성하기 (별, 눈 남았음)