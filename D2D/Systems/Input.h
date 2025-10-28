#pragma once

#define MAX_INPUT_KEY 256

class Input
{
	DECLEAR_SINGLETON(Input)

	enum
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

public:
	void Update();

	void InputProc(UINT msg, LPARAM lParam);

	bool isDown(DWORD key) const { return keyCurState[key] == DOWN; }
	bool isUp(DWORD key) const { return keyCurState[key] == UP; }
	bool isPress(DWORD key) const { return keyCurState[key] == PRESS; }

	Vector2 GetMousePos() const { return mousePos; }

	bool IsDoubleClk() const { return isDoubleClk; }

private:
	array<unsigned char, MAX_INPUT_KEY> keyState = { 0 };
	array<unsigned char, MAX_INPUT_KEY> keyPrevState = { 0 };
	array<unsigned char, MAX_INPUT_KEY> keyCurState = { 0 };
	
	Vector2 mousePos;

	bool isDoubleClk = false;
};