#include "Game.h"
#include <windows.h>
#include <iostream>

#include <time.h>

#include "../Core/Utils.h"
#include "../Core/Renderer/ASCIIRenderer.h"

//The Width of the screen
const int SCREEN_WIDTH = 256;		//*2 / 3; //resolution shrunk so i can manage with my small 1366x768 screen

//Screen Height
const int SCREEN_HEIGHT = 96;		//*2 / 3;

//The buffer before the player paddle hits the edge
const int SCREEN_MARGIN_LEFTRIGHT = 2;

//The wait for the demo to start
const int DEMO_TIMER = 250;

//The time that you can press escape to goto main menu other wise it goes back to the game
const int PAUSE_TIMER = 0.125 * 30;


//KEY CODES
#define VK_LEFT		0x25
#define VK_RIGHT	0x27
#define VK_SPACE	0x20       
#define VK_W		0x57
#define VK_A		0x41
#define VK_S		0x53
#define VK_D		0x44

Game::Game()
	:m_pRenderer(NULL)
	, m_bInitialised(false)
	, m_bExitApp(false)
{
	m_gameState = E_GAME_STATE_MAIN_MENU;
	m_pInputHandler = NULL;
	m_demoTimer = DEMO_TIMER;
	m_pauseTimer = 0;
}

Game::~Game()
{
	SAFE_DELETE_PTR(m_pRenderer);
	SAFE_DELETE_PTR(m_pInputHandler);
}


//sETS UP THE GAME WITH INITIAL VARIABLES
void Game::Initialise()
{
	InitialiseRenderer();
	m_pInputHandler = new Input();

	// THE LOGO OF THE GAME
	m_LOGO.Initialise(
"  .oooooo.                                               ooooo      ooo                                       "
" d8P'  `Y8b                                              `888b.     `8'                                       "
"888            .oooo.   ooo. .oo.  .oo.    .ooooo.        8 `88b.    8   .oooo.   ooo. .oo.  .oo.    .ooooo.  "
"888           `P  )88b  `888P\"Y88bP\"Y88b  d88' `88b       8   `88b.  8  `P  )88b  `888P\"Y88bP\"Y88b  d88' `88b "
"888     ooooo  .oP\"888   888   888   888  888ooo888       8     `88b.8   .oP\"888   888   888   888  888ooo888 "
"`88.    .88'  d8(  888   888   888   888  888    .o       8       `888  d8(  888   888   888   888  888    .o "
" `Y8bood8P'   `Y888\"\"8o o888o o888o o888o `Y8bod8P'      o8o        `8  `Y888\"\"8o o888o o888o o888o `Y8bod8P' "
		, FOREGROUND_WHITE | BACKGROUND_BLACK | BOLD_FONTTYPE, Vector2(110, 7)
	);
	m_LOGO.SetPosition(
		Vector2((SCREEN_WIDTH - m_LOGO.GetSize().x)/2,3)
			);
	m_WIN.Initialise(
		"      _____                    _____                _____          "
		"     |\\    \\                  /\\    \\              |\\    \\         "
		"     |:\\____\\                /::\\    \\             |:\\____\\        "
		"     |::|   |               /::::\\    \\            |::|   |        "
		"     |::|   |              /::::::\\    \\           |::|   |        "
		"     |::|   |             /:::/\\:::\\    \\          |::|   |        "
		"     |::|   |            /:::/__\\:::\\    \\         |::|   |        "
		"     |::|   |           /::::\\   \\:::\\    \\        |::|   |        "
		"     |::|___|______    /::::::\\   \\:::\\    \\       |::|___|______  "
		"     /::::::::\\    \\  /:::/\\:::\\   \\:::\\    \\      /::::::::\\    \\ "
		"    /::::::::::\\____\\/:::/  \\:::\\   \\:::\\____\\    /::::::::::\\____\\"
		"   /:::/~~~~/~~      \\::/    \\:::\\  /:::/    /   /:::/~~~~/~~      "
		"  /:::/    /          \\/____/ \\:::\\/:::/    /   /:::/    /         "
		" /:::/    /                    \\::::::/    /   /:::/    /          "
		"/:::/    /                      \\::::/    /   /:::/    /           "
		"\\::/    /                       /:::/    /    \\::/    /            "
		" \\/____/                       /:::/    /      \\/____/             "
		"                              /:::/    /                           "
		"                             /:::/    /                            "
		"                             \\::/    /                             "
		"                              \\/____/                              "
		, FOREGROUND_WHITE | BACKGROUND_BLACK | BOLD_FONTTYPE, Vector2(67, 21)
	);
	m_WIN.SetPosition(
		(Vector2(SCREEN_WIDTH,SCREEN_HEIGHT) - m_WIN.GetSize())/2
		);
	m_LOOSE.Initialise(
		
"          _____                   _______                  _______         "
"         /\\    \\                 /::\\    \\                /::\\    \\        "
"        /::\\    \\               /::::\\    \\              /::::\\    \\       "
"       /::::\\    \\             /::::::\\    \\            /::::::\\    \\      "
"      /::::::\\    \\           /::::::::\\    \\          /::::::::\\    \\     "
"     /:::/\\:::\\    \\         /:::/~~\\:::\\    \\        /:::/~~\\:::\\    \\    "
"    /:::/__\\:::\\    \\       /:::/    \\:::\\    \\      /:::/    \\:::\\    \\   "
"   /::::\\   \\:::\\    \\     /:::/    / \\:::\\    \\    /:::/    / \\:::\\    \\  "
"  /::::::\\   \\:::\\    \\   /:::/____/   \\:::\\____\\  /:::/____/   \\:::\\____\\ "
" /:::/\\:::\\   \\:::\\ ___\\ |:::|    |     |:::|    ||:::|    |     |:::|    |"
"/:::/__\\:::\\   \\:::|    ||:::|____|     |:::|    ||:::|____|     |:::|    |"
"\\:::\\   \\:::\\  /:::|____| \\:::\\    \\   /:::/    /  \\:::\\    \\   /:::/    / "
" \\:::\\   \\:::\\/:::/    /   \\:::\\    \\ /:::/    /    \\:::\\    \\ /:::/    /  "
"  \\:::\\   \\::::::/    /     \\:::\\    /:::/    /      \\:::\\    /:::/    /   "
"   \\:::\\   \\::::/    /       \\:::\\__/:::/    /        \\:::\\__/:::/    /    "
"    \\:::\\  /:::/    /         \\::::::::/    /          \\::::::::/    /     "
"     \\:::\\/:::/    /           \\::::::/    /            \\::::::/    /      "
"      \\::::::/    /             \\::::/    /              \\::::/    /       "
"       \\::::/    /               \\::/____/                \\::/____/        "
"        \\::/____/                 ~~                       ~~              "
"         ~~                                                                "
		, FOREGROUND_WHITE | BACKGROUND_BLACK | BOLD_FONTTYPE, Vector2(75, 21)
	);
	m_LOOSE.SetPosition(
		(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT) - m_LOOSE.GetSize()) / 2
	);

	m_PAUSED.Initialise(
"          _____                    _____                    _____                    _____                    _____                    _____          "
"         /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\         "
"        /::\\    \\                /::\\    \\                /::\\____\\                /::\\    \\                /::\\    \\                /::\\    \\        "
"       /::::\\    \\              /::::\\    \\              /:::/    /               /::::\\    \\              /::::\\    \\              /::::\\    \\       "
"      /::::::\\    \\            /::::::\\    \\            /:::/    /               /::::::\\    \\            /::::::\\    \\            /::::::\\    \\      "
"     /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/    /               /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\     "
"    /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/    /               /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/  \\:::\\    \\    "
"   /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\      /:::/    /                \\:::\\   \\:::\\    \\      /::::\\   \\:::\\    \\      /:::/    \\:::\\    \\   "
"  /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    /:::/    /      _____    ___\\:::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    /:::/    / \\:::\\    \\  "
" /:::/\\:::\\   \\:::\\____\\  /:::/\\:::\\   \\:::\\    \\  /:::/____/      /\\    \\  /\\   \\:::\\   \\:::\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/    /   \\:::\\ ___\\ "
"/:::/  \\:::\\   \\:::|    |/:::/  \\:::\\   \\:::\\____\\|:::|    /      /::\\____\\/::\\   \\:::\\   \\:::\\____\\/:::/__\\:::\\   \\:::\\____\\/:::/____/     \\:::|    |"
"\\::/    \\:::\\  /:::|____|\\::/    \\:::\\  /:::/    /|:::|____\\     /:::/    /\\:::\\   \\:::\\   \\::/    /\\:::\\   \\:::\\   \\::/    /\\:::\\    \\     /:::|____|"
" \\/_____/\\:::\\/:::/    /  \\/____/ \\:::\\/:::/    /  \\:::\\    \\   /:::/    /  \\:::\\   \\:::\\   \\/____/  \\:::\\   \\:::\\   \\/____/  \\:::\\    \\   /:::/    / "
"          \\::::::/    /            \\::::::/    /    \\:::\\    \\ /:::/    /    \\:::\\   \\:::\\    \\       \\:::\\   \\:::\\    \\       \\:::\\    \\ /:::/    /  "
"           \\::::/    /              \\::::/    /      \\:::\\    /:::/    /      \\:::\\   \\:::\\____\\       \\:::\\   \\:::\\____\\       \\:::\\    /:::/    /   "
"            \\::/____/               /:::/    /        \\:::\\__/:::/    /        \\:::\\  /:::/    /        \\:::\\   \\::/    /        \\:::\\  /:::/    /    "
"             ~~                    /:::/    /          \\::::::::/    /          \\:::\\/:::/    /          \\:::\\   \\/____/          \\:::\\/:::/    /     "
"                                  /:::/    /            \\::::::/    /            \\::::::/    /            \\:::\\    \\               \\::::::/    /      "
"                                 /:::/    /              \\::::/    /              \\::::/    /              \\:::\\____\\               \\::::/    /       "
"                                 \\::/    /                \\::/____/                \\::/    /                \\::/    /                \\::/____/        "
"                                  \\/____/                  ~~                       \\/____/                  \\/____/                  ~~              "
		, FOREGROUND_WHITE | BACKGROUND_BLACK | BOLD_FONTTYPE, Vector2(150, 21));
	m_PAUSED.SetPosition(
		(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT) - m_PAUSED.GetSize()) / 2
	);

	m_demoMode.Initialise(
"########  ######## ##     ##  #######     ##     ##  #######  ########  ######## "
"##     ## ##       ###   ### ##     ##    ###   ### ##     ## ##     ## ##       "
"##     ## ##       #### #### ##     ##    #### #### ##     ## ##     ## ##       "
"##     ## ######   ## ### ## ##     ##    ## ### ## ##     ## ##     ## ######   "
"##     ## ##       ##     ## ##     ##    ##     ## ##     ## ##     ## ##       "
"##     ## ##       ##     ## ##     ##    ##     ## ##     ## ##     ## ##       "
"########  ######## ##     ##  #######     ##     ##  #######  ########  ######## "
		,FOREGROUND_WHITE | BACKGROUND_BLACK | BOLD_FONTTYPE, Vector2(81, 7));
	m_demoMode.SetPosition(Vector2(
		(SCREEN_WIDTH - m_demoMode.GetSize().x) / 2
		, 1));


	std::vector<MenuItem*> menuItems;
	menuItems.push_back(new MenuItem(
		" ######  ########    ###    ########  ########     ######      ###    ##     ## ######## "
		"##    ##    ##      ## ##   ##     ##    ##       ##    ##    ## ##   ###   ### ##       "
		"##          ##     ##   ##  ##     ##    ##       ##         ##   ##  #### #### ##       "
		" ######     ##    ##     ## ########     ##       ##   #### ##     ## ## ### ## ######   "
		"      ##    ##    ######### ##   ##      ##       ##    ##  ######### ##     ## ##       "
		"##    ##    ##    ##     ## ##    ##     ##       ##    ##  ##     ## ##     ## ##       "
		" ######     ##    ##     ## ##    ##     ##        ######   ##     ## ##     ## ######## "
		, Vector2(89, 7), "startGame"));
	menuItems.push_back(new MenuItem(
		"######## ##     ## #### ######## "
		"##        ##   ##   ##     ##    "
		"##         ## ##    ##     ##    "
		"######      ###     ##     ##    "
		"##         ## ##    ##     ##    "
		"##        ##   ##   ##     ##    "
		"######## ##     ## ####    ##    "
		, Vector2(33, 7),"exitGame"));

	m_mainMenu.Initialize(Vector2(10, 20), menuItems);

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
	m_brickMatrix.Initialise(&m_gamePaused, &m_gameState, &m_player , Vector2(brickpos_x, 10), Vector2(bricksize_x, 10));

	m_bInitialised = true;

}

//TODO: Add comments to this file


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

//CHAGES SOME VALUES AND STUFF 
void Game::Update()
{
	m_pInputHandler->Update();


	switch (m_gameState)
	{
	case E_GAME_STATE_MAIN_MENU:
	{
		m_demoTimer--;
		if (m_demoTimer <= 0)
		{
			m_demoTimer = DEMO_TIMER;
			m_gameState = E_GAME_STATE_DEMO_GAME;
		}
		Reset();

		if (m_pInputHandler->GetKeyDown(VK_ESCAPE))
		{
			m_mainMenu.SetActive("exitGame");
		}

		
		if (0 < m_pauseTimer)
		{
			if (m_pInputHandler->GetKeyDown(VK_ESCAPE))
			{
				m_bExitApp = true;
				return;
			}
			else {
				m_pauseTimer--;
			}
		} else if (m_pInputHandler->GetKeyDown(VK_ESCAPE))
		{
			m_pauseTimer = PAUSE_TIMER;
		}

		int keysGo[2] = { VK_SPACE, VK_RETURN };
		if (m_pInputHandler->GetKeyDown(keysGo,2))
		{
			char* id = m_mainMenu.GetSelectedMenuItemID();

			if (id == "startGame")
			{
				m_gameState = E_GAME_STATE_IN_GAME;
			}

			else if (id == "demoGame")
			{
				m_gameState = E_GAME_STATE_DEMO_GAME;
			}
			else if (id == "exitGame")
			{
				m_bExitApp = true;
				return;
			}
		}
		
		int keysU[2] = { VK_W, VK_UP };
		int keysD[2] = { VK_S, VK_DOWN };
		if (m_pInputHandler->GetKeyDown(keysU,2)) {
			m_demoTimer = DEMO_TIMER;
			m_mainMenu.GoUp();
		}
		if (m_pInputHandler->GetKeyDown(keysD,2)) {
			m_demoTimer = DEMO_TIMER;
			m_mainMenu.GoDown();
		}

		m_mainMenu.Update();
	}
		break;
	case E_GAME_STATE_DEMO_GAME:
	{
		m_demoTimer--;

		if (m_demoTimer <= 0 | m_pInputHandler->AnyKeyDown())
		{
			Reset();
			m_demoTimer = DEMO_TIMER;
			m_gameState = E_GAME_STATE_MAIN_MENU;
		}
	}
	break;
	case E_GAME_STATE_IN_GAME:
	{
		m_pauseTimer = PAUSE_TIMER;
		if (m_player.GetObjectBall()->OffScreen()) {
			LightReset();
			m_player.LoseHealth(1);
			if (m_player.GetHealth() <= 0)
			{
				m_gameState = E_GAME_STATE_LOSE_GAME;
				m_player.ResetHealth();
			}
		}


		if (m_pInputHandler->GetKeyDown(VK_ESCAPE))
		{
			//uncomment when pause menu implemented
			m_gameState = E_GAME_STATE_PAUSE_MENU;
			m_gamePaused = !m_gamePaused;
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
			m_player.LoseHealth(m_player.GetHealth() / 2);
		}
		if (m_brickMatrix.BrickCount() <= 0)
		{
			m_gameState = E_GAME_STATE_WIN_GAME;
			Reset();
		}


	}
	break;
	case E_GAME_STATE_PAUSE_MENU:
	{
		if (m_pauseTimer <= 0) {
			if (m_pInputHandler->GetKeyDown(VK_ESCAPE))
			{
				m_gameState = E_GAME_STATE_IN_GAME;
			}
		}
		else
		{
			if (m_pInputHandler->GetKeyDown(VK_ESCAPE))
			{
				m_gameState = E_GAME_STATE_MAIN_MENU;
			}
			m_pauseTimer--;
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
		
		if (m_pInputHandler->GetKeyDown(VK_SPACE))
		{
			m_gameState = E_GAME_STATE_MAIN_MENU;
			Reset();
		}
	}
		break;
	default:
		break;
	};


	m_player.Update(m_pInputHandler);
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
		m_LOGO.Render(m_pRenderer);
	}
		break;
	case E_GAME_STATE_DEMO_GAME:
	case E_GAME_STATE_IN_GAME:
	{
		//m_playerPaddle.Render(m_pRenderer);
		//m_objectBall.Render(m_pRenderer);
		//m_testBrick.Render(m_pRenderer);
		m_brickMatrix.Render(m_pRenderer);
		
		m_player.Render(m_pRenderer);
		if (m_gameState==E_GAME_STATE_DEMO_GAME)
		{
			m_demoMode.Render(m_pRenderer);
		}
	}
		break;
	case E_GAME_STATE_PAUSE_MENU:
	{
		m_player.Render(m_pRenderer);
		m_PAUSED.Render(m_pRenderer);
	}
	break;
	case E_GAME_STATE_LOSE_GAME:
	{
		m_player.Render(m_pRenderer);
		m_LOOSE.Render(m_pRenderer);
	}
		break;
	case E_GAME_STATE_WIN_GAME:
		m_player.Render(m_pRenderer);
		m_WIN.Render(m_pRenderer);
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
	m_player.ResetHealth();
	m_player.ResetScore();
}
void Game::LightReset()
{
	m_player.Reset();
	//m_playerPaddle.Reset();
	//m_objectBall.Reset();
}

