#include "stdafx.h"
#include "Input.h"

Input::Input()
{

}

Input::~Input()
{

}

void Input::Update()
{
	keyPrevState = move(keyCurState);

	if (GetKeyboardState(keyCurState.data()))
	{
		for (DWORD i = 0; i < MAX_INPUT_KEY; ++i)
		{
			keyCurState[i] = (keyCurState[i] & 0x80) ? 1 : 0;

			unsigned char& PrevState = keyPrevState[i];
			unsigned char& CurState = keyCurState[i];

			if (PrevState == 0 && CurState == 1)
				keyState[i] = DOWN;
			else if (PrevState == 1 && CurState == 0)
				keyState[i] = UP;
			else if (PrevState == 1 && CurState == 1)
				keyState[i] = PRESS;
			else
				keyState[i] = NONE;
		}
	}
}

void Input::InputProc(UINT msg, LPARAM lParam)
{
	if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST)
	{
		mousePos.x = float(GET_X_LPARAM(lParam));
		mousePos.y = float(GET_Y_LPARAM(lParam));
		if (msg == WM_MBUTTONDBLCLK)
			isDoubleClk = true;
		else
			isDoubleClk = false;
	}
}
