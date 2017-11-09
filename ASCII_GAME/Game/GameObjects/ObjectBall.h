#ifndef _OBJECT_BALL_H_
#define _OBJECT_BALL_H_

#include "GameObject.h"
#include "../Sides.h"

class ObjectBall : public GameObject<ObjectBall>
{
public:
	ObjectBall();
	~ObjectBall();

	void Initialise();
	void Update();
	void Render(ASCIIRenderer* pRenderer);

private:
	Vector2 m_direction;

	bool AtWallSide(E_SIDE wallSide);
	void BounceOff(E_SIDE bounceOffSide);

	bool m_active;
	bool m_initialised;
};

#endif // !_OBJECT_BALL_H_
