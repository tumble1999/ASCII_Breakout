#ifndef _BRICK_MATRIX_H_
#define _BRICK_MATRIX_H_

#include "Brick.h"

extern Vector2 BRICK_MARGIN;

class BrickMatrix
{
public:
	BrickMatrix();
	~BrickMatrix();

	void Initialise(bool* pGamePaused, E_GAME_STATE* pGameState, Player* pPlayer, Vector2& pos, Vector2& size);
	void Update();
	void Render(ASCIIRenderer* pRenderer);


	int BrickCount();
	void Reset();

private:
	Vector2 m_pos;
	Vector2 m_size;
	std::vector<std::vector<Brick>> m_bricks;
	bool* m_pGamePaused;
	E_GAME_STATE* m_pGameState;
	Player* m_pPlayer;

	void InitialiseBricks();
	unsigned int GetColorFromY(int y);

	int GetPointsFromY(int y);

	bool m_initialised;
};

#endif // !_BRICK_MATRIX_H_
