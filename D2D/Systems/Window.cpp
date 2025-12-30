#include "stdafx.h"
#include "Window.h"
#include "Program.h"

unique_ptr<Program> Window::program = nullptr;

Window::Window(const WinDesc& initDesc)
	: desc(initDesc)
{
    WORD wHr = MyRegisterClass(desc);
    assert(wHr != 0); //생성 성공 여부 확인

    gHandle = desc.handle = CreateWindowExW
    (
        WS_EX_APPWINDOW,
        desc.appName.c_str(),
        desc.appName.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        HMENU(nullptr),
        desc.instance,
        nullptr
    );
    assert(desc.handle != nullptr); //생성 성공 여부 확인

    RECT rect = { 0, 0, LONG(desc.width), LONG(desc.height) };

    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);

    const long& winWidth = rect.right - rect.left;
    const long& winHeight = rect.bottom - rect.top;

    UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - UINT(winWidth)) / 2;
    UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - UINT(winHeight)) / 2;

    MoveWindow //윈도우 창 좌표 / 너비 재지정
    (
        desc.handle,
        centerX,
        centerY,
        winWidth,
        winHeight,
        true
    );

    ShowWindow(desc.handle, SW_SHOWNORMAL); //윈도우 창의 보여지는 방식 지정
    UpdateWindow(desc.handle);

	ShowCursor(true);
}

Window::~Window()
{
	DestroyWindow(desc.handle);
	UnregisterClassW(desc.appName.c_str(), desc.instance);
}

ATOM Window::MyRegisterClass(const WinDesc& initDesc)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = initDesc.instance;
    wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = HBRUSH(GetStockObject(GRAY_BRUSH));
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = initDesc.appName.c_str();
    wcex.hIconSm = wcex.hIcon;

    return RegisterClassExW(&wcex);
}

WPARAM Window::Run()
{
	program = make_unique<Program>();

    MSG msg;
	
    // 기본 메시지 루프입니다:
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			INPUT->Update();
			TIME->Update();

			program->Update();

			GRAPHICS->Begin();
			{
				program->Render();
			}
			GRAPHICS->End();
		}
	}

	return msg.wParam;
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INPUT->InputProc(message, lParam);

	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}