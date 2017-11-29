#include "Player.h"

#include <math.h>

Player::Player()
{
	m_health = 0;
	m_initialized = 0;
	/*m_pObjectBall = new ObjectBall;
	m_pPlayerPaddle = new PlayerPaddle;
	m_pSDHealth = new ScoreDisplay;
	m_pSDScore = new ScoreDisplay;*/
	m_score = 0;
}

Player::~Player()
{
	/*delete m_pObjectBall;
	delete m_pPlayerPaddle;
	delete m_pSDHealth;
	delete m_pSDScore;*/
}

void Player::Initialize(E_GAME_STATE *gameState, bool *gamePaused)
{
	m_playerPaddle.SetGameStatePointer(gameState);
	m_playerPaddle.SetGamePausedPointer(gamePaused);
	m_playerPaddle.SetObjectBallPointer(&m_objectBall);
	m_playerPaddle.Initialise(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 90 / 100), 0x41, 0x44, 10);

	m_objectBall.SetGameStatePointer(gameState);
	m_objectBall.SetGamePausedPointer(gamePaused);
	m_objectBall.Initialise(&m_playerPaddle);
}

void Player::Update()
{
	m_objectBall.Update();
	m_playerPaddle.Update();
}

void Player::Render(ASCIIRenderer* pRenderer)
{
	m_objectBall.Render(pRenderer);
	m_playerPaddle.Render(pRenderer);
	m_sdHealth.Render(pRenderer);
	m_sdScore.Render(pRenderer);
}

void Player::LoseHealth(int amount)
{
	m_health -= std::abs(amount);
}

void Player::GainHealth(int amount)
{
	m_health += std::abs(amount);
}

void Player::ResetHealth()
{
	m_health = 0;
}

int& Player::GetHealth()
{
	return m_health;
}

void Player::SetScore(int amount)
{
	m_score = amount;
}

void Player::AppendScore(int amount)
{
	m_score += amount;
}

void Player::ResetScore()
{
	m_score = 0;
}

int& Player::GetScore()
{
	return m_score;
}

PlayerPaddle* Player::GetPlayerPaddle()
{
	return &m_playerPaddle;
}

ObjectBall* Player::GetObjectBall()
{
	return &m_objectBall;
}

void Player::Reset()
{
	m_playerPaddle.Reset();
	m_objectBall.Reset();
}
