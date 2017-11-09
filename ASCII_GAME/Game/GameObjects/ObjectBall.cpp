#include "ObjectBall.h"

CHAR_INFO BallSprite[] = {
	PIXEL,PIXEL,PIXEL,PIXEL,
	PIXEL,PIXEL,PIXEL,PIXEL
};

ObjectBall::ObjectBall()
{
	m_initialised = false;
	m_active = false;
	m_direction = Vector2(0, 0);
}

ObjectBall::~ObjectBall()
{
}

void ObjectBall::Initialise()
{
	//VAR INITIALISATION
	m_direction = Vector2(1, 1);

	//SPRITE INITIALISATION
	Sprite::Initialise(BallSprite, Vector2(4,2));

	m_initialised = true;
}

void ObjectBall::Update()
{
	if (!m_initialised)
		return;
}

void ObjectBall::Render(ASCIIRenderer* pRenderer)
{
	if (!m_initialised)
		return;

	//Sprite rendering
	Sprite::Render(pRenderer);
}


bool ObjectBall::AtWallSide(E_SIDE wallSide)
{
	return false;
}

void ObjectBall::BounceOff(E_SIDE bounceOffSide)
{

}