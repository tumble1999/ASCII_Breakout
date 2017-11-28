#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "PlayerPaddle.h"
#include "ScoreDisplay.h"
#include "ObjectBall.h"

//extern const int SCREEN_WIDTH;

class Player
{
public:
	Player();
	~Player();

	void Initialize(E_GAME_STATE *gameState, bool *gamePaused);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

	void LoseHealth(int amount);
	void GainHealth(int amount);
	void ResetHealth();
	int& GetHealth();

	void SetScore(int amount);
	void AppendScore(int amount);
	void ResetScore();
	int& GetScore();

	PlayerPaddle* GetPlayerPaddle();

	ObjectBall* GetObjectBall();

private:
	int m_health;
	int m_score;

	PlayerPaddle* m_pPlayerPaddle;
	ObjectBall* m_pObjectBall;
	ScoreDisplay* m_pSDHealth;
	ScoreDisplay* m_pSDScore;


	int m_initialized;
};

#endif // _PLAYER_H_

