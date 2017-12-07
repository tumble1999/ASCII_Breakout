#include "Input.h"

const int KEY_COUNT = 65535;

Input::Input()
{

}

Input::~Input()
{
}

void Input::Update()
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		m_lastKeyPressed[i] = m_keyPressed[i];
		m_keyPressed[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

bool Input::GetKey(int key)
{
	return m_keyPressed[i];
}

bool Input::GetKeyDown(int key)
{
	return !m_lastKeyPressed[i] == m_keyPressed[i];
}

bool Input::GetKeyUp(int key)
{
	return m_lastKeyPressed[i] == !m_keyPressed[i];
}
