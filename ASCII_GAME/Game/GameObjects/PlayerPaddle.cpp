#include "PlayerPaddle.h"

const int MOVEMENT_SPEED = 1;
const int HEIGHT = 2;

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
	m_moveable = false;
	SetPosition(pos);

	Sprite::Initialise(GetPlayerSprite(), Vector2(GetCurrentWidth(), HEIGHT));
	
	Vector2 startPos(pos.x - (Sprite::GetSize().x/2),pos.y - Sprite::GetSize().y/2);

	m_initialised = true;
}

void PlayerPaddle::Update()
{
	if (!m_initialised)
	{
		return; //GO AWAY, THIS DOESNT EXIST YET !!!
	}
	if (GetGameState()==E_GAME_STATE_IN_GAME)
	{
		if (LeftKeyPressed())
		{
			MoveLeft();
		}
		if (RightKeyPressed())
		{
			MoveRight();
		}
	}

	//This will create an animation of the paddle changing size
	if (GetCurrentWidth() < m_newWidth)
	{
		IncreaseWidth(2);
	}
	if (GetCurrentWidth() > m_newWidth)
	{
		DecreaseWidth(2);
	}
	if (GetCurrentWidth() == m_newWidth)
	{
		m_moveable = true;
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
	MoveLeft(MOVEMENT_SPEED);
}

void PlayerPaddle::MoveRight()
{
	MoveRight(MOVEMENT_SPEED);
}

void PlayerPaddle::MoveLeft(int amount)
{
	SetPosition(GetPosition() - Vector2(amount, 0));
	if (GetPosition().x < SCREEN_MARGIN_LEFTRIGHT)
	{
		MoveRight(amount);
	}
}

void PlayerPaddle::MoveRight(int amount)
{
	SetPosition(GetPosition() + Vector2(amount, 0));

	if (GetPosition().x + GetCurrentWidth() > SCREEN_WIDTH - SCREEN_MARGIN_LEFTRIGHT)
	{
		MoveLeft(amount);
	}
}