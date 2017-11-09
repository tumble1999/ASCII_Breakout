#include "GameObject.h"

template<class T>
GameObject<T>::GameObject()
{
	m_pGameObject = new T;
}

template<class T>
GameObject<T>::GameObject(T* pGameObject)
{
	m_pGameObject = pGameObject;
}

template<class T>
GameObject<T>::~GameObject()
{
	delete m_pGameObject;
}

template<class T>
void GameObject<T>::InitialiseGameObject(E_GAME_STATE* pGameState)
{
	m_pGameState = pGameState;
}