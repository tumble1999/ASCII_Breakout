#include "Player.h"

#include <math.h>

const int INIT_HEALTH = 5;
const int INIT_SCORE = 0;

//TODO: Add comments to this file

Player::Player()
{
	m_health = INIT_HEALTH;
	m_score = INIT_SCORE;
	m_initialized = false;
	/*m_pObjectBall = new ObjectBall;
	m_pPlayerPaddle = new PlayerPaddle;
	m_pSDHealth = new ScoreDisplay;
	m_pSDScore = new ScoreDisplay;*/
}

Player::~Player()
{
	/*delete m_pObjectBall;
	delete m_pPlayerPaddle;
	delete m_pSDHealth;
	delete m_pSDScore;*/
}

//sets variables to initial and specified values
void Player::Initialize(E_GAME_STATE *gameState, bool *gamePaused)
{
	m_playerPaddle.SetGameStatePointer(gameState);
	m_playerPaddle.SetGamePausedPointer(gamePaused);
	m_playerPaddle.SetPlayerPointer(this);
	m_playerPaddle.Initialise(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 90 / 100), { 0x41, VK_LEFT }, { 0x44, VK_RIGHT }, 10);

	m_objectBall.SetGameStatePointer(gameState);
	m_objectBall.SetGamePausedPointer(gamePaused);
	m_objectBall.Initialise(&m_playerPaddle);

	UpdateScoreDisplays();

}

//keeps the player up to date with whats going  on 
void Player::Update(Input* pInputHandler)
{
	//UpdateScoreDisplay();
	m_playerPaddle.ChangeWidth(m_health*2);//NOT A BUG: CHANGING SIZE DEPENDING ON HEALTH
	m_objectBall.Update(pInputHandler);
	m_playerPaddle.Update(pInputHandler);
}

void Player::Render(ASCIIRenderer* pRenderer)
{
	for (int i = 0; i < m_sdHealth.size(); i++)
	{
		m_sdHealth[i].Render(pRenderer);
	}
	for (int i = 0; i < m_sdScore.size(); i++)
	{
		m_sdScore[i].Render(pRenderer);
	}
	m_objectBall.Render(pRenderer);
	m_playerPaddle.Render(pRenderer);
}

void Player::LoseHealth(int amount)
{
	m_health -= std::abs(amount);
	UpdateScoreDisplays();
}

void Player::GainHealth(int amount)
{
	float testValue = m_health + std::abs(amount);

	if (testValue >= 41)
	{
		testValue = 41;
	}
	m_health = testValue;
	UpdateScoreDisplays();
}

void Player::ResetHealth()
{
	m_health = INIT_HEALTH;
	UpdateScoreDisplays();
}

int& Player::GetHealth()
{
	return m_health;
}

void Player::SetScore(int amount)
{
	m_score = amount;
	UpdateScoreDisplays();
}

void Player::AppendScore(int amount)
{
	float testValue = m_score + amount;

	if (testValue > 2147483647)
	{
		testValue = 2147483647;
	}
	m_score = testValue;
	UpdateScoreDisplays();
}

void Player::ResetScore()
{
	m_score = INIT_SCORE;
	UpdateScoreDisplays();
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

//updates all the displays
void Player::UpdateScoreDisplays()
{
	//HEALTH DISPLAY
	if (m_health<0)
	{
		m_health = 0;
	}
	UpdateScoreDisplay(m_sdHealth, m_health, Vector2(1, 0));

	//SCORE DISPLAY
	if (m_score<0)
	{
		m_score = 0;
	}
	UpdateScoreDisplay(m_sdScore, m_score, 
		Vector2(SCREEN_WIDTH - 
		((static_cast<int>(std::log10(m_score)) + 1)*DIGIT_WIDTH+DIGIT_WIDTH/2+
			1),
			0));
}

//makes sure the score display is displaying the right values
void Player::UpdateScoreDisplay(std::vector<ScoreDisplay>& scoreDisplay, int& value, Vector2 pos)
{
	
	int numDigits = static_cast<int>(std::log10(value))+1;
	if (numDigits < 1) {
		numDigits = 1;
	}

	scoreDisplay = std::vector<ScoreDisplay>(numDigits, ScoreDisplay());

	for (int i = 0; i < numDigits; i++)
	{
		int digitValue = static_cast<int>(value / std::pow(10, i));
		digitValue %= 10;
		scoreDisplay[i].Initialise(pos + Vector2(DIGIT_WIDTH*(numDigits - i), DIGIT_HEIGHT / 2));
		scoreDisplay[i].SetDigitValue(digitValue);
	}
}


