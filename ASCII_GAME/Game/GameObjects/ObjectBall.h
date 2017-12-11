#ifndef _OBJECT_BALL_H_
#define _OBJECT_BALL_H_

#include "GameObject.h"
#include "../Sides.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_MARGIN_LEFTRIGHT;

class Player;
class PlayerPaddle;

class ObjectBall : public GameObject
{
public:
	ObjectBall();
	~ObjectBall();

	void Initialise(Sprite* pPlayerPaddle);
	void Update(Input* pInputHandler);
	void Render(ASCIIRenderer* pRenderer);

	void CheckSpriteCollision(Sprite& otherSprite);
	bool IsNear(Sprite& otherSprite);
	bool CollidesWith(Sprite& otherSprite);
	bool OffScreen();

	bool IsActive();


	void Reset();

private:
	Vector2 m_direction;
	Sprite m_BoundingBox;
	Sprite* m_pPlayerPaddle;

	void CheckCollision();
	void UpdatePosition();

	E_SIDE GetWallSideH();
	E_SIDE GetWallSideV();
	bool AtWallSide(E_SIDE wallSide);
	void BounceOff(E_SIDE bounceOffSide);

	E_SIDE GetSpriteSideH(Sprite& sprite);
	E_SIDE GetSpriteSideV(Sprite& sprite);

	bool m_active;
	bool m_initialised;
};

#endif // !_OBJECT_BALL_H_
