#include "Game.h"
#include <windows.h>
#include <iostream>

#include <time.h>

#include "../Core/Utils.h"
#include "../Core/Renderer/ASCIIRenderer.h"

const int SCREEN_WIDTH = 256		*2 / 3; //resolution shrunk so i can manage with my small 1366x768 screen
const int SCREEN_HEIGHT = 96		*2 / 3;
const int SCREEN_MARGIN_LEFTRIGHT = 2;

#define VK_LEFT		0x25
#define VK_RIGHT	0x27
#define VK_SPACE	0x20       

Game::Game()
	:m_pRenderer(NULL)
	, m_bInitialised(false)
	, m_bExitApp(false)
	, m_EscPressed(0)
{
	m_gameState = E_GAME_STATE_MAIN_MENU;
}

Game::~Game()
{
	SAFE_DELETE_PTR(m_pRenderer);
}

void Game::Initialise()
{
	InitialiseRenderer();

	std::vector<MenuItem*> menuItems;
	menuItems.push_back(new MenuItem(
		" ######  ########    ###    ########  ########     ######      ###    ##     ## ######## "
		"##    ##    ##      ## ##   ##     ##    ##       ##    ##    ## ##   ###   ### ##       "
		"##          ##     ##   ##  ##     ##    ##       ##         ##   ##  #### #### ##       "
		" ######     ##    ##     ## ########     ##       ##   #### ##     ## ## ### ## ######   "
		"      ##    ##    ######### ##   ##      ##       ##    ##  ######### ##     ## ##       "
		"##    ##    ##    ##     ## ##    ##     ##       ##    ##  ##     ## ##     ## ##       "
		" ######     ##    ##     ## ##    ##     ##        ######   ##     ## ##     ## ######## "
		, Vector2(89, 7)));
	menuItems.push_back(new MenuItem(
		"######## ##     ## #### ######## "
		"##        ##   ##   ##     ##    "
		"##         ## ##    ##     ##    "
		"######      ###     ##     ##    "
		"##         ## ##    ##     ##    "
		"##        ##   ##   ##     ##    "
		"######## ##     ## ####    ##    "
		, Vector2(33, 7)));

	m_mainMenu.Initialize(Vector2(0, 0), menuItems);

	//m_playerPaddle.SetGameStatePointer(&m_gameState);
	//m_playerPaddle.SetGamePausedPointer(&m_gamePaused);
	//m_playerPaddle.SetObjectBallPointer(&m_objectBall);
	//m_playerPaddle.Initialise(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT*90/100), 0x41,0x44, 10);

	//m_objectBall.SetGameStatePointer(&m_gameState);
	//m_objectBall.SetGamePausedPointer(&m_gamePaused);
	//m_objectBall.Initialise(&m_playerPaddle);
	

	m_player.Initialize(&m_gameState, &m_gamePaused);

	//m_testBrick.SetGameStatePointer(&m_gameState);
	//m_testBrick.SetGamePausedPointer(&m_gamePaused);
	//m_testBrick.SetObjectBallPointer(&m_objectBall);
	//m_testBrick.Initialise(Vector2(SCREEN_WIDTH/2,SCREEN_HEIGHT/2)-BRICK_SIZE/2, BACKGROUND_BRIGHT_RED);

	//m_brickMatrix.SetGameStatePounter(&m_gamePaused);
	//m_brickMatrix.SetGamePausedPointer(&p_gamePaused);
	//m_brickMatrix.SetObjectBallPointer(&m_objectBall);

	int bricksize_x = SCREEN_WIDTH / (
		BRICK_SIZE.x + BRICK_MARGIN.x
		);

	int gridWidth = ((BRICK_SIZE.x + BRICK_MARGIN.x)*bricksize_x);

	int brickpos_x = (SCREEN_WIDTH-gridWidth)/2;

	//m_brickMatrix.Initialise(&m_gamePaused, &m_gameState, &m_objectBall, Vector2(brickpos_x, 10), Vector2(bricksize_x, 5));
	m_brickMatrix.Initialise(&m_gamePaused, &m_gameState, &m_player , Vector2(brickpos_x, 10), Vector2(bricksize_x, 5));

	m_bInitialised = true;

}


void Game::InitialiseRenderer()
{
	m_pRenderer = new ASCIIRenderer();

	m_pRenderer->Initialise(SCREEN_WIDTH, SCREEN_HEIGHT);

}

void Game::Run()
{
	while (!m_bExitApp) // The legendary "Game Loop"
	{
		Update();

		Render();

		Sleep(30);
	}
}

void Game::Update()
{
	if (GetKeyState(VK_ESCAPE) < 0)
	{
		m_EscPressed++;
		if(m_EscPressed>=10)
		{
			m_bExitApp = true;
			return;
		}
	
	} else
	{
		m_EscPressed = 0;
	}


	switch (m_gameState)
	{
	case E_GAME_STATE_MAIN_MENU:
	{
		Reset();
		if (GetKeyState(VK_SPACE) < 0)
		{
			m_gameState = E_GAME_STATE_IN_GAME;
		}

		m_mainMenu.Update();
	}
		break;
	case E_GAME_STATE_IN_GAME:
	{
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			if (m_EscPressed>0)
			{
				//uncomment when pause menu implemented
				m_gameState = E_GAME_STATE_PAUSE_MENU;
				m_gamePaused = !m_gamePaused;
			}
		}
		if (m_player.GetHealth() <= 0)
		{
			m_gameState = E_GAME_STATE_LOSE_GAME;
			m_player.ResetHealth();
		}


		if (GetKeyState(VK_NUMPAD9) < 0)
		{
			m_player.LoseHealth(1);
		}
		if (GetKeyState(VK_NUMPAD8) < 0)
		{
			m_player.GainHealth(1);
		}
		if (GetKeyState(VK_NUMPAD5) < 0)
		{
			m_player.GainHealth(m_player.GetHealth());
		}
		if (GetKeyState(VK_NUMPAD6) < 0)
		{
			m_player.LoseHealth(m_player.GetHealth()/2);
		}

		if (m_player.GetObjectBall()->OffScreen()) {
			LightReset();
			m_player.LoseHealth(1);
			m_player.GetPlayerPaddle()->ChangeWidth(m_player.GetPlayerPaddle()->GetWidth() - 2);
		}

	}
	break;
	case E_GAME_STATE_PAUSE_MENU:
	{
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			if (m_EscPressed==1)
			{
				m_gameState = E_GAME_STATE_IN_GAME;
			}
		}
	}
		break;
	case E_GAME_STATE_LOSE_GAME:
	{
		if (GetKeyState(VK_SPACE) < 0)
		{
			m_gameState = E_GAME_STATE_MAIN_MENU;
		}
	}
		break;
	case E_GAME_STATE_WIN_GAME:
	{
		m_gameState = E_GAME_STATE_IN_GAME;
		Reset();
	}
		break;
	default:
		break;
	};


	m_player.Update();
	//m_playerPaddle.Update();
	//m_objectBall.Update();
	//m_testBrick.Update();
	m_brickMatrix.Update();
}

void Game::Render()
{
	//call this first
	m_pRenderer->ClearScreen();

	//render your game here
	switch (m_gameState)
	{
	case E_GAME_STATE_MAIN_MENU:
	{
		m_mainMenu.Render(m_pRenderer);
	}
		break;
	case E_GAME_STATE_IN_GAME:
	{
		//m_playerPaddle.Render(m_pRenderer);
		//m_objectBall.Render(m_pRenderer);
		//m_testBrick.Render(m_pRenderer);
		m_brickMatrix.Render(m_pRenderer);
		
		m_player.Render(m_pRenderer);
	}
		break;
	case E_GAME_STATE_LOSE_GAME:
	{
		m_player.Render(m_pRenderer);
	}
		break;
	case E_GAME_STATE_WIN_GAME:
		break;
	default:
		break;
	};

	//call this last
	m_pRenderer->Render();
}

void Game::Reset()
{
	m_player.Reset();
	//m_playerPaddle.Reset();
	//m_objectBall.Reset();
	m_brickMatrix.Reset();
}
void Game::LightReset()
{
	m_player.Reset();
	//m_playerPaddle.Reset();
	//m_objectBall.Reset();
}

