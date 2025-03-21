#pragma once
#include "SystemDef.h"

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2() = default;
	Vector2(float x, float y) : x(x), y(y) {};
	Vector2(POINT point) : x(point.x), y(point.y) {};
	Vector2(Float2 point) : x(point.x), y(point.y) {};

	operator Float2() { return Float2(x, y); }

	Vector2 operator+(const Vector2& value) const
	{
		return Vector2(x + value.x, y + value.y);
	}
	Vector2 operator-(const Vector2& value) const
	{
		return Vector2(x - value.x, y - value.y);
	}

	Vector2 operator*(const Vector2& value) const
	{
		return Vector2(x * value.x, y * value.y);
	}
	Vector2 operator/(const Vector2& value) const
	{
		return Vector2(x / value.x, y / value.y);
	}

	void operator+=(const Vector2& value)
	{
		x += value.x;
		y += value.y;
	}
	void operator-=(const Vector2& value)
	{
		x -= value.x;
		y -= value.y;
	}

	void operator*=(const float& value)
	{
		x *= value;
		y *= value;
	}
	void operator/=(const float& value)
	{
		x /= value;
		y /= value;
	}

	Vector2 operator* (const Matrix& value) const
	{
		Float2 coord(x, y);

		XMVECTOR temp = XMLoadFloat2(&coord);
		temp = XMVector2TransformCoord(temp, value);

	}
};
