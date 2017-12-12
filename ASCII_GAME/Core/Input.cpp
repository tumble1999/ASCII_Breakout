#include "Input.h"


//Sets everything to 0.
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

//chages current key staes to past keystates and updates the current key states
void Input::Update()
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		m_lastKeyPressed[i] = m_keyPressed[i];
		//m_keyPressed[i] = GetAsyncKeyState(i) & 0x8000;
		m_keyPressed[i] = GetKeyState(i) < 0;
	}
}

//gets current key state
bool Input::GetKey(int key)
{
	return m_keyPressed[key];
}


//gets if key was just pressed
bool Input::GetKeyDown(int key)
{
	return !m_lastKeyPressed[key] && m_keyPressed[key];
}

//gets if key was just released
bool Input::GetKeyUp(int key)
{
	return m_lastKeyPressed[key] && !m_keyPressed[key];
}


//returns true if any of the current keys are helt down
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


//return true if any of the specifoed keys where just pressed
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

//returns true if any of the specified keys 
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

//returns true if anykey is helt down
bool Input::AnyKeyDown() {
	for (int i = 0; i < KEY_COUNT; i++)
	{
		if (GetKeyDown(i))
		{
			return true;
		}
	}
	return false;
}
