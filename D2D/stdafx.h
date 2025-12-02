// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#ifdef _DEBUG //디버그 빌드 일때 콘솔창 열기
#pragma comment (linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <windowsx.h>
// C 런타임 헤더 파일입니다.
#include <cassert>

// C++ 런타임 헤더 파일입니다.
#include <string>
#include <memory>
#include <array>
#include <chrono>
#include <iostream>
#include <vector>


//DirectX D3D11
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

// WRL
#include <wrl.h>
using namespace Microsoft;
using namespace WRL;

//DirectXToolKit stuff
#include "_Libraries/DXToolKit/SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

using namespace std;


//define
#define WIN_DEFAULT_WIDTH 1280.0f
#define WIN_DEFAULT_HEIGHT 720.0f
#define CHECK(hr) { assert(SUCCEEDED(hr)); }

#define CENTER Vec2(WIN_DEFAULT_WIDTH / 2, WIN_DEFAULT_HEIGHT / 2)

#define DECLEAR_SINGLETON(CLASS_NAME) 						\
private:	/*인수로 넣은 클래스의 생성자와 소멸자를 private로 지정하여 외부에서 객체생성을 막는다*/\
CLASS_NAME();												\
~CLASS_NAME();												\
public:														\
CLASS_NAME(const CLASS_NAME& other) = delete;	/*복사 생성 막기*/\
CLASS_NAME& operator=(const CLASS_NAME& other) = delete;	\
CLASS_NAME(const CLASS_NAME&& other) = delete;				\
CLASS_NAME& operator=(const CLASS_NAME&& other) = delete;	\
															\
static CLASS_NAME* Get()									\
{															\
	static CLASS_NAME instance;								\
	return &instance;										\
}

//GROBAL var
extern HWND gHandle;
extern float gWinWidth;
extern float gWinHeight;

// Utilities 파일 헤더

// Systems 파일 헤더
#include "Systems/Input.h"
#include "Systems/Time.h"
#include "Systems/Graphics.h"

#define INPUT Input::Get()
#define TIME Time::Get()
#define DELTA TIME->GetDeltaTime()
#define GRAPHICS Graphics::Get()
#define DEVICE GRAPHICS->GetDivece()
#define DEVICECONTEXT GRAPHICS->GetDiveceConText()

// Headers
#include "Renders/Resources/VertexType.h"
#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/Shaders/Shader.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/Resources/ConstantBuffer.h"
#include "Renders/Resources/GlobalBuffers.h"

// Objects
#include "Objects/ColorRect.h"