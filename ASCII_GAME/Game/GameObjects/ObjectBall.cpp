#include "ObjectBall.h"
#include <windows.h>

const int SPEED = 1;
const WORD BALL_COLOR = BACKGROUND_YELLOW;
const CHAR_INFO BALL_PIXEL = PIXEL_COLORED(BALL_COLOR);
const CHAR_INFO BALL_BOUNDING_PIXEL = PIXEL_COLORED(BACKGROUND_BRIGHT_GREEN);

CHAR_INFO BallSprite[] = {
	BALL_PIXEL, BALL_PIXEL, BALL_PIXEL, BALL_PIXEL,
	BALL_PIXEL, BALL_PIXEL, BALL_PIXEL, BALL_PIXEL
};
CHAR_INFO BallBoundingSprite[] = {
	BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,
	BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,
	BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,
	BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,
	BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,
	BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL,BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL, BALL_BOUNDING_PIXEL
};



//TODO: Add comments to this file


ObjectBall::ObjectBall()
{
	m_initialised = false;
	m_active = false;
	m_direction = Vector2(0, 0);
	m_pPlayerPaddle = NULL;
}

ObjectBall::~ObjectBall()
{
}

void ObjectBall::Initialise(Sprite* pPlayerPaddle)
{
	//VAR INITIALISATION
	m_direction = Vector2(SPEED, -SPEED);
	m_pPlayerPaddle = pPlayerPaddle;

	//SPRITE INITIALISATION
	Sprite::Initialise(BallSprite, Vector2(2,1));
	m_BoundingBox.Initialise(BallBoundingSprite, GetSize()+Vector2(2,1)*2);
	
	//Vector2 startPos(pos.x - (Sprite::GetSize().x / 2), pos.y - Sprite::GetSize().y / 2);
	//SetPosition(startPos);
	UpdatePosition();

	m_initialised = true;
}

void ObjectBall::Update(Input* pInputHandler)
{
	if (!m_initialised)
	{
		return;
	}
	if (!GameStateIs({ E_GAME_STATE_IN_GAME,E_GAME_STATE_DEMO_GAME })|GamePaused())
		return;

	if (GameStateIs(E_GAME_STATE_DEMO_GAME) & !m_active)
	{
		m_active = true;
	}

	UpdatePosition();

	if (m_active)
	{
		CheckCollision();
	}
	else
	{
		int keysBallRelease[2] = { VK_SPACE, VK_RETURN };
		bool spaceStatus = pInputHandler->GetKeyUp(keysBallRelease,2);

		if (spaceStatus)
		{
			m_active = true;
			return;
		}
	}
}

void ObjectBall::Render(ASCIIRenderer* pRenderer)
{
	if (!m_initialised|GamePaused())
		return;
	if (!GameStateIs({ E_GAME_STATE_IN_GAME,E_GAME_STATE_DEMO_GAME }))
		return;

	// Sprite rendering
	//m_BoundingBox.Render(pRenderer);
	Sprite::Render(pRenderer);
}

void ObjectBall::CheckCollision()
{

	if (GetWallSideV() != E_SIDE_BOTTOM)
	{
		BounceOff(GetWallSideH());
		BounceOff(GetWallSideV());
	}
}


void ObjectBall::UpdatePosition()
{
	Vector2 newPos;

	if (m_active)
	{
		newPos = GetPosition() + m_direction;
	}
	else
	{
		newPos = m_pPlayerPaddle->GetPosition() +
			Vector2
			(
			(m_pPlayerPaddle->GetSize().x - GetSize().x) / 2,
				-GetSize().y
			);
	}

	SetPosition(newPos);

	Vector2 boundingPos = (m_BoundingBox.GetSize() - GetSize()) / 2;
	m_BoundingBox.SetPosition(GetPosition() - boundingPos);
}

void ObjectBall::CheckSpriteCollision(Sprite& otherSprite)
{
	if (IsNear(otherSprite))
	{
		BounceOff(GetSpriteSideH(otherSprite));
		BounceOff(GetSpriteSideV(otherSprite));
	}
}

bool ObjectBall::IsNear(Sprite & otherSprite)
{
	return m_BoundingBox.Collides(otherSprite);
}

bool ObjectBall::CollidesWith(Sprite & otherSprite)
{
	return IsNear(otherSprite)&((GetSpriteSideH(otherSprite) != E_SIDE_NULL) | (GetSpriteSideV(otherSprite) != E_SIDE_NULL));
}

bool ObjectBall::OffScreen()
{
	return GetWallSideV() == E_SIDE_BOTTOM;
}

bool ObjectBall::IsActive()
{
	return m_active;
}


//sees if the ball is on the left or right wall
E_SIDE ObjectBall::GetWallSideH()
{
	E_SIDE wallSide = E_SIDE_NULL;
	int xPos = GetPosition().x;

	if (xPos <= 0)
	{
		wallSide = E_SIDE_LEFT;
	}	
	else if (SCREEN_WIDTH <= xPos + GetSize().x)
	{
		wallSide = E_SIDE_RIGHT;
	}
	return wallSide;
}

//sees if the ball is on the top or bottom wall
E_SIDE ObjectBall::GetWallSideV()
{
	E_SIDE wallSide = E_SIDE_NULL;
	int yPos = GetPosition().y;
	if (yPos <= 0)
	{
		wallSide = E_SIDE_TOP;
	} 
	else if (SCREEN_HEIGHT<= yPos + GetSize().y)
	{
		wallSide = E_SIDE_BOTTOM;
	}

	return wallSide;
}

bool ObjectBall::AtWallSide(E_SIDE wallSide)
{
	return (wallSide == GetWallSideH())|(wallSide == GetWallSideV());
}





void ObjectBall::BounceOff(E_SIDE bounceOffSide)
{
	switch (bounceOffSide)
	{
	case E_SIDE_TOP:
	{
		//Beep(257, 100);//b
		PlaySound(TEXT("sound/b.wav"), NULL, SND_FILENAME | SND_ASYNC);
		m_direction = Vector2(m_direction.x, SPEED);
	}
		break;
	case E_SIDE_BOTTOM: {
		//Beep(262, 100);//c
		PlaySound(TEXT("sound/c.wav"), NULL, SND_FILENAME | SND_ASYNC);
		m_direction = Vector2(m_direction.x, -SPEED);
	}
		break;
	case E_SIDE_LEFT:
	{
		//Beep(370, 100);//f#
		PlaySound(TEXT("sound/f#.wav"), NULL, SND_FILENAME | SND_ASYNC);
		m_direction = Vector2(SPEED, m_direction.y);
	}
		break;
	case E_SIDE_RIGHT:
	{
		//Beep(392, 100);//g
		PlaySound(TEXT("sound/g.wav"), NULL, SND_FILENAME | SND_ASYNC);
		m_direction = Vector2(-SPEED, m_direction.y);
	}
		break;
	default:
		break;
	}
}

void ObjectBall::Reset()
{
	m_active = false;
}


//works out where the sprite is in relation to the ball
E_SIDE ObjectBall::GetSpriteSideH(Sprite& sprite)
{
	E_SIDE spriteSide = E_SIDE_NULL;
	int BallMin = GetPosition().x;
	int BallMax = BallMin + GetSize().x;

	int SpriteMin = sprite.GetPosition().x;
	int SpriteMax = SpriteMin + sprite.GetSize().x;
	
	if (BallMax <= SpriteMin)
	{
		spriteSide = E_SIDE_RIGHT;
	}
	if (SpriteMax <= BallMin)
	{
		spriteSide = E_SIDE_LEFT;
	}

	return spriteSide;
}
//works out where the sprite is in relation to the ball
E_SIDE ObjectBall::GetSpriteSideV(Sprite& sprite)
{
	E_SIDE spriteSide = E_SIDE_NULL;
	int BallMin = GetPosition().y;//TOP SIDE
	int BallMax = BallMin + GetSize().y;//BOTTOM, SIDE

	int SpriteMin = sprite.GetPosition().y;//TOP SIDE
	int SpriteMax = SpriteMin + sprite.GetSize().y;//BOTTOM SIDE

	if (BallMax <= SpriteMin)
	{
		spriteSide = E_SIDE_BOTTOM;
	}
	if (SpriteMax <= BallMin)
	{
		spriteSide = E_SIDE_TOP;
	}

	return spriteSide;
}