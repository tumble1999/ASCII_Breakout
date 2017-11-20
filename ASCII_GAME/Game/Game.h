#ifndef _GAME_H_
#define _GAME_H_

#include "GameObjects\PlayerPaddle.h"
#include "GameObjects\ObjectBall.h"
#include "GameObjects\BrickMatrix.h"

class ASCIIRenderer;

class Game
{
public:
	Game();
	~Game();

	void Initialise();
	void Run();

private:

	//Functions
	void InitialiseRenderer();
	void Update();
	void Render();

	void Reset();
	void LightReset();

	//Variables
	ASCIIRenderer* m_pRenderer;
	E_GAME_STATE m_gameState;
	bool m_gamePaused;

	bool m_bInitialised;
	bool m_bExitApp;

	int m_EscPressed;

	//Objects
	PlayerPaddle m_playerPaddle;
	ObjectBall m_objectBall;
	Brick m_testBrick;
	BrickMatrix m_brickMatrix;
};


#endif
