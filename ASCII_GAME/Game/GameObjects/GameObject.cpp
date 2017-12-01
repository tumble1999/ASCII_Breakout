#include "GameObject.h"

#include "..\..\Core\Utils.h"
#include "..\GameObjects\Player.h"

GameObject::GameObject()
{
	m_pGameState = NULL;
	m_pGamePaused = NULL;
	m_pObjectBall = NULL;
}

GameObject::~GameObject()
{
	//SAFE_DELETE_PTR(m_pGameState);
}



E_GAME_STATE GameObject::GetGameState() const
{ 
	return *m_pGameState;
}

bool GameObject::GameStateIs(E_GAME_STATE gameState)
{
	return *m_pGameState == gameState;
}

bool GameObject::GameStateIs(std::vector<E_GAME_STATE> gameStates)
{
	bool output = false;

	for (int i = 0; i < gameStates.size(); i++)
	{
		output |= gameStates[i] == *m_pGameState;
	}

	return output;
}

void GameObject::SetGameStatePointer(E_GAME_STATE* pGameState)
{
	m_pGameState = pGameState;
}

void GameObject::SetGameState(E_GAME_STATE gameState)
{
	*m_pGameState = gameState;
}

bool GameObject::GamePaused()
{
	return *m_pGamePaused;
}

void GameObject::SetGamePausedPointer(bool * pGamePaused)
{
	m_pGamePaused = pGamePaused;
}

void GameObject::SetGamePaused(bool paused)
{
	*m_pGamePaused = paused;
}

ObjectBall * GameObject::GetObjectBall()
{
	return m_pPlayer->GetObjectBall();
}

Player * GameObject::GetPlayer()
{
	return m_pPlayer;
}

void GameObject::SetPlayerPointer(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}

bool GameObject::KeyPressed(int key)
{
	return GetKeyState(key) & 0x8000;
}

bool GameObject::KeyToggle(int key)
{
	return GetKeyState(key) & 1;
}

bool GameObject::KeyDown(int key)
{
	return KeyToggle(key) & KeyPressed(key);
}

bool GameObject::KeyUp(int key)
{
	return KeyToggle(key) & !KeyPressed(key);
}

