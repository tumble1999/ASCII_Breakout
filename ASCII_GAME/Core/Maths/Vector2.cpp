#include "Vector2.h"

Vector2::Vector2()
:x(0)
,y(0)
{

}

Vector2::Vector2(int _x, int _y)
:x(_x)
,y(_y)
{

}

Vector2::~Vector2()
{

}

Vector2 Vector2::operator+()
{
	return *this;
}
Vector2 Vector2::operator+(Vector2 a)
{
	return Vector2(x + a.x, y + a.y);
}

Vector2 Vector2::operator+(int a)
{
	return Vector2(x + a, y + a);
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator-(Vector2 a)
{
	return Vector2(x - a.x, y - a.y);
}

Vector2 Vector2::operator-(int a)
{
	return Vector2(x - a, y - a);
}

Vector2 Vector2::operator*(float a)
{
	return Vector2((int) (x*a),(int) (y*a));
}

Vector2 Vector2::operator*(int a)
{
	return  Vector2(x * a, y * a);
}

Vector2 Vector2::operator/(float a)
{
	return  Vector2((int)(x / a),(int)( y / a));
}

Vector2 Vector2::operator/(int a)
{
	return Vector2(x / a, y / a);
}
