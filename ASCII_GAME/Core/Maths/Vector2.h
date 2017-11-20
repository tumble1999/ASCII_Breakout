#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	Vector2();
	Vector2(int _x, int _y);
	~Vector2();

	int x;
	int y;

	Vector2 operator +();
	Vector2 operator +(Vector2 a);
	Vector2 operator +(int a);

	Vector2 operator -();
	Vector2 operator -(Vector2 a);
	Vector2 operator -(int a);

	Vector2 operator *(Vector2 a);
	Vector2 operator *(float a);
	Vector2 operator *(int a);

	Vector2 operator /(float a);
	Vector2 operator /(int a);

private:
};

#endif
