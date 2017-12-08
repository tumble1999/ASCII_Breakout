#include "Input.h"



Input::Input()
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		m_lastKeyPressed[i] = false;
		m_keyPressed[i] = false;
	}
}

Input::~Input()
{
}

void Input::Update()
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		m_lastKeyPressed[i] = m_keyPressed[i];
		//m_keyPressed[i] = GetAsyncKeyState(i) & 0x8000;
		m_keyPressed[i] = GetKeyState(i) < 0;
	}
}

bool Input::GetKey(int key)
{
	return m_keyPressed[key];
}

bool Input::GetKeyDown(int key)
{
	return !m_lastKeyPressed[key] && m_keyPressed[key];
}

bool Input::GetKeyUp(int key)
{
	return m_lastKeyPressed[key] && !m_keyPressed[key];
}

bool Input::GetKey(int * key, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (GetKey(key[i]))
		{
			return true;
		}
	}
	return false;
}

bool Input::GetKeyDown(int * key, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (GetKeyDown(key[i]))
		{
			return true;
		}
	}
	return false;
}

bool Input::GetKeyUp(int * key, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (GetKeyUp(key[i]))
		{
			return true;
		}
	}
	return false;
}

