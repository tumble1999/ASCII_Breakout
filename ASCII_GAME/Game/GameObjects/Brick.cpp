#include "Brick.h"
#include "ObjectBall.h"

Vector2 BRICK_SIZE = Vector2(8, 2);

Brick::Brick()
{

	m_destroyed = false;
	m_initialised = false;
}

Brick::~Brick()
{
	if (!m_destroyed)
	{
		Destroy();
	}
}

void Brick::Initialise(Vector2 & pos, unsigned short color)
{
	if (m_initialised)
		return;

	InitialiseBlockSprite(color);
	Sprite::Initialise(GetBlockSpriteArray(), BRICK_SIZE);
	Sprite::SetPosition(pos);

	m_initialised = true;
}

void Brick::Update()
{
	if (!m_initialised)
		return;

	CheckBallCollision();

	Sprite::SetPixels(GetBlockSpriteArray());
}

void Brick::Render(ASCIIRenderer * pRenderer)
{
	if (!m_initialised|m_destroyed)
		return;

	Sprite::Render(pRenderer);
}

void Brick::Destroy()
{
	if (!m_initialised)
		return; 

	m_destroyed = true;
}

bool Brick::Destroyed()
{
	return m_destroyed;
}

void Brick::CheckBallCollision()
{
	GetObjectBall()->CheckSpriteCollision(*this);

	if (GetObjectBall()->CollidesWith(*this))
	{
		Destroy();
	}
}

void Brick::InitialiseBlockSprite(unsigned short color)
{
	if (m_initialised)
		return;

	CHAR_INFO BRICK_PIXEL = PIXEL_COLORED(color);

	m_BrickSprite.clear();

	for (int i = 0; i < BRICK_SIZE.x*BRICK_SIZE.y; i++)
	{
		m_BrickSprite.push_back(BRICK_PIXEL);
	}
}

CHAR_INFO* Brick::GetBlockSpriteArray()
{
	return m_BrickSprite.data();
}
