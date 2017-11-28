#include "Player.h"

Player::Player()
{
	m_health = 0;
	m_initialized = 0;
	m_playerPaddle = new PlayerPaddle;
	m_score = 0;
	m_sdHealth = new ScoreDisplay;
	m_sdScore = new ScoreDisplay;
}

Player::~Player()
{
	delete m_playerPaddle;
	delete m_sdHealth;
	delete m_sdScore;
}

void Player::Initialize()
{
	m_playerPaddle.SetGameStatePointer(&m_gameState);
	m_playerPaddle.SetGamePausedPointer(&m_gamePaused);
	m_playerPaddle.SetObjectBallPointer(&m_objectBall);
	m_playerPaddle.Initialise(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 90 / 100), 0x41, 0x44, 10);
}

void Player::Update()
{
}

void Player::Render(ASCIIRenderer* pRenderer)
{
}

void Player::LoseHealth(int amount)
{
}

void Player::GainHealth(int amount)
{
}

void Player::ResetHealth()
{
}

int& Player::GetHealth()
{
	// TODO: insert return statement here
}

void Player::SetScore(int amount)
{
}

void Player::AppendScore(int amount)
{
}

void Player::ResetScore()
{
}

int& Player::GetScore()
{
	// TODO: insert return statement here
}

PlayerPaddle* Player::GetPlayerPaddle()
{
	// TODO: insert return statement here
}

ObjectBall* Player::GetObjectBall()
{
	// TODO: insert return statement here
}
