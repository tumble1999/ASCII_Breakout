#include "PlayerPaddle.h"
#include "ObjectBall.h"

const int ACCELERATION = 1;
const int TOP_SPEED = 10;
const int HEIGHT = 2;

std::vector<CHAR_INFO> PlayerSprite;

//TODO: Add comments to this file

PlayerPaddle::PlayerPaddle()
{
	m_initialised = false;
	m_INIT_WIDTH = 0;
	m_moveable = false;
	m_newWidth = 0;
	m_speed = 0;
	m_demo = false;
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::Initialise(Vector2& pos, std::vector<int> leftKey, std::vector<int> rightKey, int width)
{

	m_leftKey = leftKey;
	m_rightKey = rightKey;
	m_newWidth = 2*width;
	m_moveable = false;
	m_INIT_WIDTH = width;
	SetPosition(pos);

	Sprite::Initialise(
		GetPlayerSprite(), 
		Vector2(
			GetCurrentWidth()//+5   //commenting out '+5' fixes: read access violation.
			, HEIGHT//+5
		)
	);
	
	m_startPos = Vector2(pos.x - (Sprite::GetSize().x/2),pos.y - Sprite::GetSize().y/2);

	m_initialised = true;
}


void PlayerPaddle::Update(Input* pInputHandler)
{
	if (!m_initialised)
		return;
	if (!GameStateIs({ E_GAME_STATE_IN_GAME ,E_GAME_STATE_DEMO_GAME}))
		return;

	if (GameStateIs(E_GAME_STATE_DEMO_GAME))
	{
		m_demo = true;
	}
	else
	{
		m_demo = false;
	}

	

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

		if (m_demo)
		{
			SetPosition(Vector2(
				GetObjectBall()->GetPosition().x -
				(GetSize().x - GetObjectBall()->GetSize().x) / 2
				, GetPosition().y
			));
		}
		else
		{
			if (LeftKeyPressed(pInputHandler) | RightKeyPressed(pInputHandler))
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
			if (LeftKeyPressed(pInputHandler))
			{
				MoveLeft();
			}
			if (RightKeyPressed(pInputHandler))
			{
				MoveRight();
			}
		}

		
	}
}

//displays the player paddle to the screen
void PlayerPaddle::Render(ASCIIRenderer* pRenderer)
{
	if (!m_initialised)
	{
		return;//GO AWAY, THIS DOESNT EXIST YET !!!
	}
	if (!GameStateIs({ E_GAME_STATE_IN_GAME,E_GAME_STATE_DEMO_GAME }))
		return;
	Sprite::Render(pRenderer);
}

//modifyes the width of the paddle
void PlayerPaddle::ChangeWidth(int newSize)
{
	m_newWidth = 2*newSize;
}

const int PlayerPaddle::GetWidth()
{
	return m_newWidth/2;
}

bool PlayerPaddle::GetDemo()
{
	return m_demo;
}

//resets the values to the initial values
void PlayerPaddle::Reset()
{
	SetPosition(m_startPos);
	ChangeWidth(m_INIT_WIDTH);
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

//Makes the paddle Bigger
void PlayerPaddle::IncreaseWidth(int amount)
{
	for (int i = 0; i < 2*amount; i++)
	{
		PlayerSprite.push_back(PIXEL);
	}
	Sprite::SetPixels(GetPlayerSprite(), Vector2(GetCurrentWidth(), HEIGHT));
	MoveLeft(amount/2);
}

//shrinks the paddle
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
	if (GetObjectBall()->IsActive())
	{
		GetObjectBall()->CheckSpriteCollision(*this);
	}
}

bool PlayerPaddle::LeftKeyPressed(Input* pInputHandler)
{
	return (pInputHandler->GetKey(m_leftKey.data(), m_leftKey.size()));
}

bool PlayerPaddle::RightKeyPressed(Input* pInputHandler)
{
	return (pInputHandler->GetKey(m_rightKey.data(), m_rightKey.size()));
}


void PlayerPaddle::MoveLeft()
{
	MoveLeft(m_speed);
}

void PlayerPaddle::MoveRight()
{
	MoveRight(m_speed);
}


//moves the paddle right
void PlayerPaddle::MoveLeft(int amount)
{
	SetPosition(GetPosition() - Vector2(amount, 0));
	if (GetPosition().x < SCREEN_MARGIN_LEFTRIGHT)
	{
		SetPosition(Vector2(SCREEN_MARGIN_LEFTRIGHT,GetPosition().y));
	}
}

//moves the paddle left
void PlayerPaddle::MoveRight(int amount)
{
	SetPosition(GetPosition() + Vector2(amount, 0));

	if (GetPosition().x + GetCurrentWidth() > SCREEN_WIDTH - SCREEN_MARGIN_LEFTRIGHT)
	{
		SetPosition(Vector2(SCREEN_WIDTH - SCREEN_MARGIN_LEFTRIGHT - GetCurrentWidth(), GetPosition().y));
	}
}
