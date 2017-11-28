#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "PlayerPaddle.h"
#include "ScoreDisplay.h"

class Player
{
public:
	Player();
	~Player();

	void Initialize();
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

	ObjectBall * GetObjectBall();

private:
	int m_health;
	int m_score;

	PlayerPaddle* m_playerPaddle;
	ScoreDisplay* m_sdHealth;
	ScoreDisplay* m_sdScore;


	int m_initialized;
};

#endif // _PLAYER_H_

