#ifndef _BRICK_MATRIX_H_
#define _BRICK_MATRIX_H_

#include "Brick.h"

class BrickMatrix
{
public:
	BrickMatrix();
	~BrickMatrix();

	void Initialise(bool* pGamePaused, E_GAME_STATE* pGameState, Vector2& pos, Vector2& size);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

private:
	Vector2 m_pos;
	Vector2 m_size;
	std::vector<std::vector<Brick>> m_bricks;
	bool* m_pGamePaused;
	E_GAME_STATE* m_pGameState;

	void InitialiseBricks();

	bool m_initialised;
};

#endif // !_BRICK_MATRIX_H_
