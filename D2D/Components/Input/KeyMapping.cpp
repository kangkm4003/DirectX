#include "stdafx.h"
#include "KeyMapping.h"

void KeyMapping::Update()
{
	SUPER::Update();

	if (INPUT->Down(curMappedKey))
	{
		onKeyDown();
	}
	if (INPUT->Press(curMappedKey))
	{
		onKeyPress();
	}
	if (INPUT->Up(curMappedKey))
	{
		onKeyUp();
	}
}

void KeyMapping::Render()
{
	SUPER::Render();
}

void KeyMapping::onKeyDown()
{

}

void KeyMapping::onKeyUp()
{

}

void KeyMapping::onKeyPress()
{

}
