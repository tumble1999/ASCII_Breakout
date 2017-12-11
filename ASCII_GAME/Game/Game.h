#ifndef _GAME_H_
#define _GAME_H_

#include "GameObjects\PlayerPaddle.h"
#include "GameObjects\ObjectBall.h"
#include "GameObjects\BrickMatrix.h"
#include "Menus\Menu.h"
#include "../Core/Input.h"

#include "GameObjects\Player.h"


class ASCIIRenderer;

class Game
{
public:
	Game();
	~Game();

	void Initialise();
	void Run();

private:

	// Functions
	void InitialiseRenderer();
	void Update();
	void Render();

	void Reset();
	void LightReset();

	// Variables
	ASCIIRenderer* m_pRenderer;
	Input* m_pInputHandler;
	E_GAME_STATE m_gameState;
	bool m_gamePaused;
	int m_demoTimer;

	bool m_bInitialised;
	bool m_bExitApp;

	int m_EscPressed;

	// Objects

	Sprite m_LOGO;
	Sprite m_WIN;
	Sprite m_LOOSE;
	Sprite m_PAUSED;
	Player m_player;

	//PlayerPaddle m_playerPaddle;
	//ObjectBall m_objectBall;
	//Brick m_testBrick;
	BrickMatrix m_brickMatrix;

	Menu m_mainMenu;
};


#endif
