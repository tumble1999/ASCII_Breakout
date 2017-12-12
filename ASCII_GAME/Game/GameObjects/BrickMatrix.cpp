#include "BrickMatrix.h"

Vector2 BRICK_MARGIN = Vector2(0,1);

/*
TODO:	# Colors depending on y. done
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
	m_pPlayer = NULL;
	m_bricks = std::vector<std::vector<Brick>>();
}

BrickMatrix::~BrickMatrix()
{
}

//sets all values to specified
void BrickMatrix::Initialise(bool* pGamePaused, E_GAME_STATE* pGameState, Player* pPlayer, Vector2 & pos = Vector2(0,0), Vector2 & size=Vector2(1,1))
{
	m_pos = pos;
	m_size = size;
	m_pGamePaused = pGamePaused;
	m_pGameState = pGameState;
	m_pPlayer = pPlayer;

	InitialiseBricks();

	m_initialised = true;
}

//updates all of the bricks
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

//tells all of the bricks to render
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


//sets up all of theb bricks with initial  values and 
//calculates x and y values based on position in array
void BrickMatrix::InitialiseBricks()
{
	m_bricks = std::vector<std::vector<Brick>>(m_size.y, std::vector<Brick>(m_size.x, Brick()));
	for (int y = 0; y < m_size.y; y++)
	{
		//gets the color based on the y pos
		unsigned int colorForCurrentRow = GetColorFromY(y);
		//gets the points based on the y pos
		int pointsForCurrentRow = GetPointsFromY(y);
		for (int x = 0; x < m_size.x; x++)
		{
			//sets the position based on the id in the array
			Vector2 pos = m_pos + (
				(BRICK_SIZE+BRICK_MARGIN) * Vector2(x,y)
				);

			//initialising the brick's values
			m_bricks[y][x].SetGamePausedPointer(m_pGamePaused);
			m_bricks[y][x].SetGameStatePointer(m_pGameState);
			m_bricks[y][x].SetPlayerPointer(m_pPlayer);
			m_bricks[y][x].Initialise(pointsForCurrentRow, pos, colorForCurrentRow);
			//FIXED:(error: deconstructs after second brick made)
		}
	}
}

/* Ratios to convert to and from
matrix size	:	brick pos y
color count	:	color id

color count	=	matrix size	*	?
color id	=	brick pos y		*	?

we dont know color id
but we do know: matrix size, brick pos y, color count

?	=	color count	/	matrix size
color id = brick pos y * (color count/matrix size)
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

//same as above but with points
int BrickMatrix::GetPointsFromY(int y)
{
	std::vector<unsigned int> colors =
	{ 100, 70, 20, 10 };

	float multiplier = 0;
	int id = 0;

	multiplier = ((float)colors.size()) / ((float)m_size.y);
	id = multiplier * y;

	return colors[id];
}


//reinitialises the bricks
void BrickMatrix::Reset()
{
	InitialiseBricks();
}

//counts the non desryed bricks
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
