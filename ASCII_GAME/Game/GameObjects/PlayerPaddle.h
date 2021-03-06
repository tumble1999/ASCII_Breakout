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

	void Initialise(Vector2& pos, std::vector<int> leftKey, std::vector<int> rightKey, int width);
	void Update(Input* pInputHandler);
	void Render(ASCIIRenderer* pRenderer);

	void ChangeWidth(int newWidth);
	const int GetWidth();
	bool GetDemo();

	void Reset();

private:
	int m_INIT_WIDTH;

	bool m_moveable;
	bool m_initialised;
	bool m_demo;

	int m_speed;

	std::vector<int> m_leftKey;
	std::vector<int> m_rightKey;

	int m_newWidth;

	Vector2 m_startPos;

	void CheckBallCollision();

	bool LeftKeyPressed(Input* pInputHandler);
	bool RightKeyPressed(Input* pInputHandler);

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