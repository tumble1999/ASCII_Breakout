#include "BrickMatrix.h"

Vector2 BRICK_MARGIN = Vector2(0,1);

/*
TODO:	# Colors depending on y.
		# ...
		# ...
*/

BrickMatrix::BrickMatrix()
{
	m_initialised = false;
	m_pos = Vector2(0, 0);
	m_size = Vector2(0, 0);
	m_pGameState = NULL;
	m_pGamePaused = NULL;
	m_pObjectBall = NULL;
	m_bricks = std::vector<std::vector<Brick>>();
}

BrickMatrix::~BrickMatrix()
{
}

void BrickMatrix::Initialise(bool* pGamePaused, E_GAME_STATE* pGameState, ObjectBall* pObjectBall, Vector2 & pos = Vector2(0,0), Vector2 & size=Vector2(1,1))
{
	m_pos = pos;
	m_size = size;
	m_pGamePaused = pGamePaused;
	m_pGameState = pGameState;
	m_pObjectBall = pObjectBall;

	InitialiseBricks();

	m_initialised = true;
}

void BrickMatrix::Update()
{
	if (!m_initialised )
		return;

	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			m_bricks[y][x].Update();
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
		unsigned int colorForCurrentRow = GetColorFromY(y);
		for (int x = 0; x < m_size.x; x++)
		{
			Vector2 pos = m_pos + (
				(BRICK_SIZE+BRICK_MARGIN) * Vector2(x,y)
				);

			m_bricks[y][x].SetGamePausedPointer(m_pGamePaused);
			m_bricks[y][x].SetGameStatePointer(m_pGameState);
			m_bricks[y][x].SetObjectBallPointer(m_pObjectBall);
			m_bricks[y][x].Initialise(pos, colorForCurrentRow);
			//FIXED:(error: deconstructs after second brick made)
		}
	}
}

/*
colors:id
size:y
*/

unsigned int BrickMatrix::GetColorFromY(int y)
{
	std::vector<unsigned int> colors = 
	{BACKGROUND_BRIGHT_RED, BACKGROUND_YELLOW, BACKGROUND_BRIGHT_GREEN, BACKGROUND_BRIGHT_BLUE};

	float multiplier = 0;
	int id = 0;

	multiplier = ((float)colors.size())/((float)m_size.y);
	id = multiplier * y;

	return colors[id];
}

void BrickMatrix::Reset()
{
	InitialiseBricks();
}

int BrickMatrix::BrickCount()
{
	int count = 0;
	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			if (!m_bricks[y][x].Destroyed())
			{
				count++;
			}
		}
	}
	return count;
}
