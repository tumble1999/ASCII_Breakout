#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <Windows.h>
#include <vector>

#include "../GameStates.h"
#include "../../Core/Maths/Vector2.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include "../../Core/Renderer/SpriteTools.h"
#include "../../Core/Renderer/Sprite.h"

template<class T>
class GameObject: public Sprite
{
public:
	GameObject();
	GameObject(T* gameObject);
	~GameObject();

	void InitialiseGameObject(E_GAME_STATE* pGameState);

	// T => GameObject
	GameObject operator=(T gameObject) { return GameObject(gameObject); }
	// GameObject => T
	operator T*() { return m_pGameObject; }

	E_GAME_STATE GetGameState() { return *m_pGameState; }
	void SetGameState(E_GAME_STATE newState) { *m_pGameState = newState; }

private:
	T* m_pGameObject;
	E_GAME_STATE* m_pGameState;
};

#endif // !_GAME_OBJECT_H_
