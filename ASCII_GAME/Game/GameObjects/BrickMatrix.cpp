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

void BrickMatrix::Initialise(Vector2 & pos = Vector2(0,0), Vector2 & size=Vector2(1,1))
{
	m_pos = pos;
	m_size = size;

	InitialiseBricks();

	m_initialised = true;
}

void BrickMatrix::Update()
{
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
	m_bricks.clear();
	for (int y = 0; y < m_size.y; y++)
	{
		std::vector<Brick>* currrentRow = new std::vector<Brick>();
		for (int x = 0; x < m_size.x; x++)
		{
			Brick* currentBrick = new Brick();
			Vector2 currentBrickPos = Vector2(x,y);
			currentBrick->Initialise(m_pos+currentBrickPos, BACKGROUND_WHITE);
			currrentRow->push_back(*currentBrick);
			//error: deconstructs after second brick made
		}
		m_bricks.push_back(*currrentRow);
	}
}
