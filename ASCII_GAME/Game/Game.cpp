#include "Game.h"
#include <windows.h>
#include <iostream>

#include <time.h>

#include "../Core/Utils.h"
#include "../Core/Renderer/ASCIIRenderer.h"

#include "GameObjects\ScoreDisplay.h"

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 96;

int testScore_value = 0;
ScoreDisplay testScore_scoreDisplay;
Vector2 testScore_Position(30, 5);

#define VK_LEFT		0x25
#define VK_RIGHT	0x27
#define VK_SPACE	0x20       

Game::Game()
	:m_pRenderer(NULL)
	, m_bInitialised(false)
	, m_bExitApp(false)
{
	m_GameState = E_GAME_STATE_MAIN_MENU;
}

Game::~Game()
{
	SAFE_DELETE_PTR(m_pRenderer);
}

void Game::Initialise()
{
	InitialiseRenderer();

	m_bInitialised = true;

	testScore_scoreDisplay.Initialise(testScore_Position);
	testScore_scoreDisplay.SetDigitValue(testScore_value);

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

	testScore_value++;
	testScore_value %= 10;
	testScore_scoreDisplay.SetDigitValue(testScore_value);

	switch (m_GameState)
	{
	case E_GAME_STATE_MAIN_MENU:
	{
		
	}
	default:
		break;
	}
}

void Game::Render()
{
	//call this first
	m_pRenderer->ClearScreen();

	//render your game here
	testScore_scoreDisplay.Render(m_pRenderer);

	//call this last
	m_pRenderer->Render();
}

