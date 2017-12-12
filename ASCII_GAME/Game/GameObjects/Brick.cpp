#include "Brick.h"
#include "Player.h"

Vector2 BRICK_SIZE = Vector2(8, 2);

Brick::Brick()
{
	m_destroyed = false;
	m_initialised = false;
	m_BrickSprite = std::vector<CHAR_INFO>();
	m_points = 10;
}

Brick::~Brick()
{
	if (!m_destroyed)
	{
		//Destroy();
	}
}

//sets variables to specified values
void Brick::Initialise(int points ,Vector2 & pos, unsigned short color) {
	m_points = points;
	Initialise(pos, color);
}


//sets variables to specified values
void Brick::Initialise(Vector2 & pos, unsigned short color)
{
	if (m_initialised)
		return;

	InitialiseBrickSprite(color);
	Sprite::Initialise(GetBrickSpriteArray(), BRICK_SIZE);
	Sprite::SetPosition(pos);

	m_initialised = true;
}

//amkes sure pixels are set
void Brick::Update()
{
 	if (!m_initialised | m_destroyed)
		return;

	CheckBallCollision();

	Sprite::SetPixels(GetBrickSpriteArray());
}

/*
tells the sprite class to display the brick#

pRenderer: the rendering engine to use.
*/
void Brick::Render(ASCIIRenderer * pRenderer)
{
	if (!m_initialised | m_destroyed)
		return;

	Sprite::Render(pRenderer);
}

//destrys the brick
void Brick::Destroy()
{
	if (!m_initialised | m_destroyed)
		return;

	m_destroyed = true;
}


//returns true if the brick is destryed
bool Brick::Destroyed()
{
	return m_destroyed;
}


//checks ball collission
void Brick::CheckBallCollision()
{
	if (!m_initialised | m_destroyed)
		return;


	if (GetObjectBall()->CollidesWith(*this))
	{
		GetObjectBall()->CheckSpriteCollision(*this);
		GetPlayer()->AppendScore(m_points);
		Destroy();
	}
	
}

//initialises the sprite
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


//gets the sprite information
CHAR_INFO* Brick::GetBrickSpriteArray()
{
	return m_BrickSprite.data();
}
