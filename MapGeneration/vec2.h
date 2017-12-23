#pragma once
/////////////////////////////////////////////////
// Class Vec2
class Vec2
{
public:
	Vec2(float X = 0, float Y = 0);

	Vec2 operator+(const Vec2& a);
	Vec2 operator-(const Vec2& a);
	Vec2 operator+=(const Vec2& a);
	Vec2 operator*(const float& a);
	Vec2 operator*(const Vec2& a);
	Vec2 operator/(const float& a);
	bool operator==(const Vec2& a);

	Vec2 normalize();
	Vec2 magnitude(float ragius);
	float length();

	float x;
	float y;
};

