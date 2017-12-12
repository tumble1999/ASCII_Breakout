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









/*

		A WAY OF ANY GAME OBJECT RETRIVING THE GAME STATE

*/
E_GAME_STATE GameObject::GetGameState() const
{ 
	return *m_pGameState;
}
bool GameObject::GameStateIs(E_GAME_STATE gameState)
{
	return *m_pGameState == gameState;
}

//iterates through every game state specified to se if one of them match
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







/*

		LETS ANY GAME OBJECT SEE IF THE GAME IS PAUSED

*/

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







/*

LETS ANY GAME OBJECT MANAGE THE BALL AND COLIDE WITH IT

*/

ObjectBall * GameObject::GetObjectBall()
{
	return m_pPlayer->GetObjectBall();
}









/*

LETS ANY GAME OBJECT MANAGE THE PLAYER
*/

Player * GameObject::GetPlayer()
{
	return m_pPlayer;
}

void GameObject::SetPlayerPointer(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}


