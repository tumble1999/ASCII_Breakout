#include "Input.h"

const int KEY_COUNT = 65535;

Input::Input()
{
	m_keyPressed = { false };
}

Input::~Input()
{
}

void Input::Update()
{
	m_lastKeyPressed = m_keyPressesd;
	for (int i = 0; i < KEY_COUNT; i++)
	{
		m_keyPressed[i] = GetKey(i);
	}
}

bool Input::GetKey(int key)
{
	return false;
}

bool Input::GetKeyDown(int key)
{
	return false;
}

bool Input::GetKeyUp(int key)
{
	return false;
}
