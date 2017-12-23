//////////////////////////////////////////////////
// Include 
#include "vec2.h"
#include <cmath>

//////////////////////////////////////////////////
// Class Vec2
Vec2::Vec2(float X, float Y)
{
	x = X;
	y = Y;
}

Vec2 Vec2::normalize()
{
	float length = sqrtf(x*x + y*y);

	Vec2 tmp;
	if (length == 0) 
		return tmp;

	tmp.x = x / length;
	tmp.y = y / length;

	return tmp;
}

Vec2 Vec2::magnitude(float radius)
{
	if(length() > radius) return normalize() * radius;
	else return *this;
}

float Vec2::length()
{
	return sqrtf(x*x + y*y);
}

Vec2 Vec2::operator+(const Vec2& a)
{
	Vec2 tmp;
	tmp.x += x + a.x;
	tmp.y += y + a.y;
	return tmp;
}

Vec2 Vec2::operator+=(const Vec2& a)
{
	return *this = *this + a;
}

Vec2 Vec2::operator*(const float& a)
{
	Vec2 tmp;
	tmp.x = x * a;
	tmp.y = y * a;
	return tmp;
}

Vec2 Vec2::operator*(const Vec2& a)
{
	Vec2 tmp;
	tmp.x = x * a.x;
	tmp.y = y * a.y;
	return tmp;
}

Vec2 Vec2::operator/(const float& a)
{
	Vec2 tmp;
	tmp.x = x / a;
	tmp.y = y / a;
	return tmp;
}

Vec2 Vec2::operator-(const Vec2& a)
{
	Vec2 tmp;
	tmp.x = x - a.x;
	tmp.y = y - a.y;
	return tmp;
}

bool Vec2::operator==(const Vec2& a)
{
	if ((x == a.x) && (y == a.y)) return true;
	else return false;
}