#ifndef _INPUT_H_
#define _INPUT_H_

#include <windows.h>

const int KEY_COUNT = 256;

class Input
{
public:
	Input();
	~Input();

	void Update();

	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	bool GetKey(int* key, int n);
	bool GetKeyDown(int* key, int n);
	bool GetKeyUp(int* key, int n);

	bool AnyKeyDown();

private:
	bool m_keyPressed[KEY_COUNT];
	bool m_lastKeyPressed[KEY_COUNT];


};

#endif // _INPUT_H_