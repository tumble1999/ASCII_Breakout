#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <Windows.h>
#include "../Maths/Vector2.h"

class ASCIIRenderer;

class Sprite
{
public:

	Sprite();
	~Sprite();

	void Initialise(int* pixels, Vector2& size);
	void Initialise(CHAR_INFO* pixels, Vector2& size);
	void Initialise(char* pixels, int attributes, Vector2& size);

	void Render(ASCIIRenderer* pRenderer);

	void SetPixels(int* pixels, Vector2& size) { m_Size = size; SetPixels(pixels); };
	void SetPixels(CHAR_INFO* pixels, Vector2& size) { m_Size = size; SetPixels(pixels); };
	void SetPixels(char* pixels, int attributes, Vector2& size) { m_Size = size; SetPixels(pixels, attributes); };

	void SetPixels(int* pixels);
	void SetPixels(CHAR_INFO* pixels);
	void SetPixels(char* pixels, int attributes);

	void SetPosition(int x, int y){ m_Position.x = x; m_Position.y = y; }
	void SetPosition(Vector2& position){ m_Position = position; }

	Vector2 GetPosition(){ return m_Position; }
	Vector2 GetSize(){ return m_Size; }

	bool Collides(Sprite& otherSprite);

private:

	Vector2 m_Position;
	Vector2 m_Size;

	CHAR_INFO** m_PixelData;

	bool m_bInitialised;
};

#endif
