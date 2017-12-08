#ifndef _PlayerPaddle_H_
#define _PlayerPaddle_H_

#include "GameObject.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_MARGIN_LEFTRIGHT;

class PlayerPaddle : public GameObject
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Initialise(Vector2& pos, int leftKey, int rightKey, int width);
	void Update(Input* pInputHandler);
	void Render(ASCIIRenderer* pRenderer);

	void ChangeWidth(int newWidth);
	const int GetWidth();

	void Reset();

private:

	bool m_moveable;
	bool m_initialised;

	int m_speed;
	int m_leftKey;
	int m_rightKey;
	int m_newWidth;

	Vector2 m_startPos;

	void CheckBallCollision();

	bool LeftKeyPressed();
	bool RightKeyPressed();

	int GetCurrentWidth() const;
	CHAR_INFO* GetPlayerSprite();

	void MoveLeft();
	void MoveRight();
	void MoveLeft(int amount);
	void MoveRight(int amount);

	void IncreaseWidth(int amount);
	void DecreaseWidth(int amount);

};

#endif