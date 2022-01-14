#pragma once
#include <cstdint>

class Vec2
{
public:
	float x, y;
	Vec2();
	Vec2(float x, float y);
	Vec2 operator+(const Vec2& other);
	void operator+=(const Vec2& other);
	Vec2 operator-(const Vec2& other);
	void operator-=(const Vec2& other);
	float operator*(const Vec2& other);
	Vec2 operator*(float scale);
	Vec2 operator/(float scale);
	float magnitudeSquared();
	float magnitude();
	float dot(const Vec2& other);
	Vec2 normalize();
};

struct Color {
	Color(uint8_t r, uint8_t g, uint8_t b);
	uint8_t r, g, b;
	Color operator+(const Color& other);
	void operator+=(const Color& other);
};