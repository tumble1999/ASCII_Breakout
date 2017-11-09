#ifndef _GAME_H_
#define _GAME_H_

#include "GameObjects\PlayerPaddle.h"
#include "GameObjects\ObjectBall.h"

class ASCIIRenderer;

class Game
{
public:
	Game();
	~Game();

	void Initialise();
	void Run();

private:
	E_GAME_STATE m_gameState;

	//Functions
	void InitialiseRenderer();
	void Update();
	void Render();

	//Variables
	ASCIIRenderer* m_pRenderer;

	bool m_bInitialised;
	bool m_bExitApp;

	//Objects
	PlayerPaddle m_playerPaddle;
	ObjectBall m_objectBall;
};


#endif
