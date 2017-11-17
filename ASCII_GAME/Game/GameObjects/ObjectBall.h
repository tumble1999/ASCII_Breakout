#ifndef _OBJECT_BALL_H_
#define _OBJECT_BALL_H_

#include "GameObject.h"
#include "../Sides.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_MARGIN_LEFTRIGHT;

class ObjectBall : public GameObject
{
public:
	ObjectBall();
	~ObjectBall();

	void Initialise(Sprite* pPlayerPaddle);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

	void CheckSpriteCollision(Sprite& otherSprite);
	bool IsNear(Sprite& otherSprite);
	bool CollidesWith(Sprite& otherSprite);

private:
	Vector2 m_direction;
	Sprite m_BoundingBox;
	Sprite* m_pPlayerPaddle;

	void CheckCollision();

	E_SIDE GetWallSideH();
	E_SIDE GetWallSideV();
	bool AtWallSide(E_SIDE wallSide);
	void BounceOff(E_SIDE bounceOffSide);
	void Reset();

	E_SIDE GetSpriteSideH(Sprite& sprite);
	E_SIDE GetSpriteSideV(Sprite& sprite);

	bool m_active;
	bool m_initialised;
};

#endif // !_OBJECT_BALL_H_
