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
    desc.appName = L"TestWinName";
    desc.instance = hInstance;
    desc.handle = nullptr;
    desc.width = gWinWidth;
    desc.height = gWinHeight;

    auto window = make_unique<Window>(desc);
    //Window* windowPtr = new Window(desc); (이쪽이 성능이 조금더 좋음 대신 수동으로 delete 해야됨)
    //delete windowPtr;

    WPARAM wParam = window->Run();

    return int(wParam);
}