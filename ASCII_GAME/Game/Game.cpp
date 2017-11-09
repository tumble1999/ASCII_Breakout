#include "Game.h"
#include <windows.h>
#include <iostream>

#include <time.h>

#include "../Core/Utils.h"
#include "../Core/Renderer/ASCIIRenderer.h"

const int SCREEN_WIDTH = 256   *2/3; //resolution shrunk so i can manage with my small 1366x768 screen
const int SCREEN_HEIGHT = 96   *2/3;
const int SCREEN_MARGIN_LEFTRIGHT = 2;

#define VK_LEFT		0x25
#define VK_RIGHT	0x27
#define VK_SPACE	0x20       

Game::Game()
	:m_pRenderer(NULL)
	, m_bInitialised(false)
	, m_bExitApp(false)
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

	m_playerPaddle.InitialiseGameObject(&m_gameState);
	m_playerPaddle.Initialise(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT*90/100), 0x41,0x44, 10);

	m_objectBall.InitialiseGameObject(&m_gameState);
	m_objectBall.Initialise();

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
		m_bExitApp = true;
		return;
	}

	switch (m_gameState)
	{
	case E_GAME_STATE_MAIN_MENU:
		if (GetKeyState(VK_SPACE))
		{
			m_gameState =  E_GAME_STATE_IN_GAME;
		}
		break;
	case E_GAME_STATE_IN_GAME:
	break;
	case E_GAME_STATE_PAUSE_GAME:
		break;
	case E_GAME_STATE_LOSE_GAME:
		break;
	case E_GAME_STATE_WIN_GAME:
		break;
	default:
		break;
	};
	m_playerPaddle.Update();
	m_objectBall.Update();
}

void Game::Render()
{
	//call this first
	m_pRenderer->ClearScreen();

	//render your game here
	switch (m_gameState)
	{
	case E_GAME_STATE_MAIN_MENU:
		break;
	case E_GAME_STATE_IN_GAME:
	{
		m_playerPaddle.Render(m_pRenderer);
		m_objectBall.Render(m_pRenderer);
	}
		break;
	case E_GAME_STATE_PAUSE_GAME:
		break;
	case E_GAME_STATE_LOSE_GAME:
		break;
	case E_GAME_STATE_WIN_GAME:
		break;
	default:
		break;
	};

	//call this last
	m_pRenderer->Render();
}

