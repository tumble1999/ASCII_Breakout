#ifndef _GAME_H_
#define _GAME_H

#include "GameStates.h"
#include "../Core/Renderer/Sprite.h"
#include <vector>

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

	//Variables
	ASCIIRenderer* m_pRenderer;

	bool m_bInitialised;
	bool m_bExitApp;
};


#endif
