#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <Windows.h>
#include <vector>

#include "../GameStates.h"
#include "../../Core/Maths/Vector2.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include "../../Core/Renderer/SpriteTools.h"
#include "../../Core/Renderer/Sprite.h"

class ObjectBall;

class GameObject: public Sprite
{
public:

	GameObject();
	~GameObject();

	E_GAME_STATE GetGameState() const;
	bool GameStateIs(E_GAME_STATE gameState);
	bool GameStateIs(std::vector<E_GAME_STATE> gameState);
	void SetGameStatePointer(E_GAME_STATE* pGameState);
	void SetGameState(E_GAME_STATE gameState);


	bool GamePaused();
	void SetGamePausedPointer(bool* pGamePaused);
	void SetGamePaused(bool paused);

	ObjectBall* GetObjectBall();
	void SetObjectBallPointer(ObjectBall* pObjectBall);



	void DoNothing()
	{

	}

	bool KeyPressed(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);

private:
	E_GAME_STATE* m_pGameState;
	bool* m_pGamePaused;
	ObjectBall* m_pObjectBall;

	bool KeyToggle(int key);
};

#endif // !_GAME_OBJECT_H_