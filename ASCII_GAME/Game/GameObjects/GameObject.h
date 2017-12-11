#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <Windows.h>
#include <vector>

#include "../GameStates.h"
#include "../../Core/Input.h"
#include "../../Core/Maths/Vector2.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include "../../Core/Renderer/SpriteTools.h"
#include "../../Core/Renderer/Sprite.h"

class ObjectBall;
class Player;

class GameObject: public Sprite
{
public:

	GameObject();
	virtual ~GameObject();

	E_GAME_STATE GetGameState() const;
	bool GameStateIs(E_GAME_STATE gameState);
	bool GameStateIs(std::vector<E_GAME_STATE> gameState);
	void SetGameStatePointer(E_GAME_STATE* pGameState);
	void SetGameState(E_GAME_STATE gameState);


	bool GamePaused();
	void SetGamePausedPointer(bool* pGamePaused);
	void SetGamePaused(bool paused);

	ObjectBall* GetObjectBall();

	Player* GetPlayer();
	void SetPlayerPointer(Player* pPlayer);


	//Function usefull for break points where there is no code where i want the brakpoint
	void DoNothing(){}

	//bool KeyPressed(int key);
	//bool KeyDown(int key);
	//bool KeyUp(int key);

private:
	E_GAME_STATE* m_pGameState;
	bool* m_pGamePaused;
	ObjectBall* m_pObjectBall;
	Player* m_pPlayer;

	bool KeyToggle(int key);
};

#endif // !_GAME_OBJECT_H_