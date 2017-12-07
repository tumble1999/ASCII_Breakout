#ifndef _INPUT_H_
#define _INPUT_H_

#include <windows.h>

extern const int KEY_COUNT;

class Input
{
public:
	Input();
	~Input();

	void Update();

	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

private:
	bool keyPressed[KEY_COUNT];


};

#endif // _INPUT_H_

