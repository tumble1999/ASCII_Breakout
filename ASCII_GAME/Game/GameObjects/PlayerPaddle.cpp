#include "PlayerPaddle.h"
#include "ObjectBall.h"

const int ACCELERATION = 1;
const int TOP_SPEED = 10;
const int HEIGHT = 2;

const bool DEMO = false;

std::vector<CHAR_INFO> PlayerSprite;

PlayerPaddle::PlayerPaddle()
{
	m_initialised = false;
	this->m_leftKey = 0;
	this->m_rightKey = 0;
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::Initialise(Vector2& pos, int leftKey, int rightKey, int width)
{

	m_leftKey = leftKey;
	m_rightKey = rightKey;
	m_newWidth = 2*width;
	m_speed = 0;
	m_moveable = false;
	SetPosition(pos);

	Sprite::Initialise(GetPlayerSprite(), Vector2(GetCurrentWidth(), HEIGHT));
	
	m_startPos = Vector2(pos.x - (Sprite::GetSize().x/2),pos.y - Sprite::GetSize().y/2);

	m_initialised = true;
}

void PlayerPaddle::Update()
{
	if (!m_initialised)
		return;
	if (!GameStateIs(E_GAME_STATE_IN_GAME))
		return;

	

	//This will create an animation of the paddle changing size
	if (GetCurrentWidth() < m_newWidth)
	{
		SetGamePaused(true);
		IncreaseWidth(2);
	}
	if (GetCurrentWidth() > m_newWidth)
	{
		SetGamePaused(true);
		DecreaseWidth(2);
	}
	if (GetCurrentWidth() == m_newWidth)
	{
		SetGamePaused(false);
	}

	if (!GamePaused())
	{
		CheckBallCollision();

		if (DEMO)
		{
			SetPosition(Vector2(
				GetObjectBall()->GetPosition().x -
				(GetSize().x - GetObjectBall()->GetSize().x) / 2
				, GetPosition().y
			));
		}

		if (LeftKeyPressed() | RightKeyPressed())
		{
			if (m_speed < TOP_SPEED)
			{
				m_speed += ACCELERATION;
			}
			else
			{
				m_speed = TOP_SPEED;
			}
		}
		else
		{
			m_speed = 0;
		}
		if (LeftKeyPressed())
		{
			MoveLeft();
		}
		if (RightKeyPressed())
		{
			MoveRight();
		}
	}
}

void PlayerPaddle::Render(ASCIIRenderer* pRenderer)
{
	if (!m_initialised)
	{
		return;//GO AWAY, THIS DOESNT EXIST YET !!!
	}

	Sprite::Render(pRenderer);
}

void PlayerPaddle::ChangeWidth(int newSize)
{
	m_newWidth = 2*newSize;
}

const int PlayerPaddle::GetWidth()
{
	return m_newWidth/2;
}

void PlayerPaddle::Reset()
{
	SetPosition(m_startPos);
}


int PlayerPaddle::GetCurrentWidth() const
{
	const int width = PlayerSprite.size() / HEIGHT;
	return width;
}

CHAR_INFO* PlayerPaddle::GetPlayerSprite()
{
	CHAR_INFO* playerSpriteArray = PlayerSprite.data();
	return playerSpriteArray;
}


void PlayerPaddle::IncreaseWidth(int amount)
{
	for (int i = 0; i < 2*amount; i++)
	{
		PlayerSprite.push_back(PIXEL);
	}
	Sprite::SetPixels(GetPlayerSprite(), Vector2(GetCurrentWidth(), HEIGHT));
	MoveLeft(amount/2);
}

void PlayerPaddle::DecreaseWidth(int amount)
{
	for (int i = 0; i < 2*amount; i++)
	{
		PlayerSprite.pop_back();
	}
	Sprite::SetPixels(GetPlayerSprite(), Vector2(GetCurrentWidth(), HEIGHT));
	MoveRight(amount/2);
}


void PlayerPaddle::CheckBallCollision()
{
	GetObjectBall()->CheckSpriteCollision(*this);
}

bool PlayerPaddle::LeftKeyPressed()
{
	return (GetKeyState(m_leftKey) < 0);
}

bool PlayerPaddle::RightKeyPressed()
{
	return (GetKeyState(m_rightKey) < 0);
}


void PlayerPaddle::MoveLeft()
{
	MoveLeft(m_speed);
}

void PlayerPaddle::MoveRight()
{
	MoveRight(m_speed);
}

void PlayerPaddle::MoveLeft(int amount)
{
	SetPosition(GetPosition() - Vector2(amount, 0));
	if (GetPosition().x < SCREEN_MARGIN_LEFTRIGHT)
	{
		SetPosition(Vector2(SCREEN_MARGIN_LEFTRIGHT,GetPosition().y));
	}
}

void PlayerPaddle::MoveRight(int amount)
{
	SetPosition(GetPosition() + Vector2(amount, 0));

	if (GetPosition().x + GetCurrentWidth() > SCREEN_WIDTH - SCREEN_MARGIN_LEFTRIGHT)
	{
		SetPosition(Vector2(SCREEN_WIDTH - SCREEN_MARGIN_LEFTRIGHT - GetCurrentWidth(), GetPosition().y));
	}
}
