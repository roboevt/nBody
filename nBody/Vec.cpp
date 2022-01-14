#include "Vec.h"
#include <math.h>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& other) {
	return { this->x + other.x, this->y + other.y };
}
void Vec2::operator+=(const Vec2& other) {
	*this = *this + other;
}
Vec2 Vec2::operator-(const Vec2& other) {
	return { this->x - other.x, this->y - other.y };
}
void Vec2::operator-=(const Vec2& other) {
	*this = *this + other;
}
Vec2 Vec2::operator*(float scale) {
	return { this->x * scale, this->y * scale };
}
float Vec2::operator*(const Vec2& other) {
	return this->dot(other);
}
Vec2 Vec2::operator/(float scale) {
	return *this * (1.0f / scale);
}
float Vec2::magnitudeSquared() {
	return x * x + y * y;
}
float Vec2::magnitude() {
	return sqrt(this->magnitudeSquared());
}
float Vec2::dot(const Vec2& other) {
	return this->x * other.x + this->y + other.y;
}
Vec2 Vec2::normalize() {
	return *this / this->magnitude();
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

Color Color::operator+(const Color& other) {
	return Color(r + other.r, g + other.g, b + other.b);
}

void Color::operator+=(const Color& other) {
	*this = *this + other;
}