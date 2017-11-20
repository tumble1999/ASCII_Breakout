#include "Brick.h"
#include "ObjectBall.h"

Vector2 BRICK_SIZE = Vector2(8, 2);

Brick::Brick()
{
	m_destroyed = false;
	m_initialised = false;
	m_BrickSprite = std::vector<CHAR_INFO>();
}

Brick::~Brick()
{
	if (!m_destroyed)
	{
		//Destroy();
	}
}

void Brick::Initialise(Vector2 & pos, unsigned short color)
{
	if (m_initialised)
		return;

	InitialiseBrickSprite(color);
	Sprite::Initialise(GetBrickSpriteArray(), BRICK_SIZE);
	Sprite::SetPosition(pos);

	m_initialised = true;
}

void Brick::Update()
{
 	if (!m_initialised | m_destroyed)
		return;

	CheckBallCollision();

	Sprite::SetPixels(GetBrickSpriteArray());
}

void Brick::Render(ASCIIRenderer * pRenderer)
{
	if (!m_initialised | m_destroyed)
		return;

	Sprite::Render(pRenderer);
}

void Brick::Destroy()
{
	if (!m_initialised | m_destroyed)
		return;

	m_destroyed = true;
}

bool Brick::Destroyed()
{
	return m_destroyed;
}

void Brick::CheckBallCollision()
{
	if (!m_initialised | m_destroyed)
		return;

	if (GetObjectBall()->CollidesWith(*this))
	{
		GetObjectBall()->CheckSpriteCollision(*this);
		Destroy();
	}
	
}

void Brick::InitialiseBrickSprite(unsigned short color)
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

CHAR_INFO* Brick::GetBrickSpriteArray()
{
	return m_BrickSprite.data();
}
