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

}

void BrickMatrix::Render(ASCIIRenderer* pRenderer)
{
}

void BrickMatrix::InitialiseBricks()
{
	for (int y = 0; y < m_size.y; y++)
	{
		for (int x = 0; x < m_size.x; x++)
		{
			m_pBricks[y]
		}
	}
}
