#ifndef _BRICK_H_
#define _BRICK_H_

#include "GameObject.h"

extern Vector2 BRICK_SIZE;

class Brick : public GameObject
{
public:
	Brick();
	~Brick();

	void Initialise(Vector2& pos, unsigned short color);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

	void Destroy();

	bool Destroyed();
private:
	bool m_destroyed;
	std::vector<CHAR_INFO> m_BrickSprite;

	void CheckBallCollision();

	void InitialiseBrickSprite(unsigned short color);
	CHAR_INFO* GetBrickSpriteArray();

	bool m_initialised;
};

#endif // !_BRICK_H_
