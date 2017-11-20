#include "BrickMatrix.h"

BrickMatrix::BrickMatrix()
{
	m_initialised = false;
	m_pos = Vector2(0, 0);
	m_size = Vector2(0, 0);
}

BrickMatrix::~BrickMatrix()
{
}

void BrickMatrix::Initialise(bool* pGamePaused, E_GAME_STATE* pGameState, Vector2 & pos = Vector2(0,0), Vector2 & size=Vector2(1,1))
{
	m_pos = pos;
	m_size = size;
	m_pGamePaused = pGamePaused;
	m_pGameState = pGameState;

	InitialiseBricks();

	m_initialised = true;
}

void BrickMatrix::Update()
{
	if (!m_initialised | *m_pGameState != E_GAME_STATE_IN_GAME | *m_pGamePaused)
		return;

	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			m_bricks.at(y).at(x).Update();
		}
	}
}

void BrickMatrix::Render(ASCIIRenderer* pRenderer)
{
	if (!m_initialised)
		return;

	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			m_bricks[y][x].Render(pRenderer);
		}
	}
}

void BrickMatrix::InitialiseBricks()
{
	m_bricks = std::vector<std::vector<Brick>>(m_size.y, std::vector<Brick>(m_size.x, Brick()));
	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			Vector2 pos = m_pos + (
				(BRICK_SIZE+Vector2(2,1)) * Vector2(x,y)
				);

			m_bricks[y][x].SetGamePausedPointer(m_pGamePaused);
			m_bricks[y][x].SetGameStatePointer(m_pGameState);
			m_bricks[y][x].Initialise(pos, BACKGROUND_WHITE);
			//error: deconstructs after second brick made
		}
	}
}
