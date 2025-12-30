#pragma once

#define MAX_INPUT_KEY 256

class Input
{
	DECLARE_SINGLETON(Input)

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
	};

public:
	void Update();

	void InputProc(UINT message, LPARAM lParam);

public:
	bool Down(DWORD key) const { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool Up(DWORD key) const { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool Press(DWORD key) const { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }

	Vector2 GetMousePos() const { return mousePos; }
	
	bool IsDblClk() const { return isDblClk; }

private:
	array<unsigned char, MAX_INPUT_KEY> keyState = { 0 };
	array<unsigned char, MAX_INPUT_KEY> keyOldState = { 0 };
	array<unsigned char, MAX_INPUT_KEY> keyMap = { 0 };

	Vector2 mousePos;
	
	bool isDblClk = false;
};