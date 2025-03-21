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

		//w값 1 -> 행렬에 곱할때 1이면 이동연산 포함
		//XMVector2TransformCoord == (x,y,z,1) 
		//XMVector2TransformNormal 이동 안함 w == 0
		temp = XMVector2TransformCoord(temp, value);
		XMStoreFloat2(&coord,temp);
		return coord;
	}

	void operator*= (const Matrix& value)
	{
		Float2 coord(x, y);
		XMVECTOR temp = XMLoadFloat2(&coord);
		temp = XMVector2TransformCoord(temp, value);
		XMStoreFloat2(&coord, temp);
		x = coord.x;
		y = coord.y;
	}
	bool operator==(const Vector2& value) const
	{
		return x == value.x && y == value.y;
	}

	float Length() const
	{
		return sqrtf((x * x) + (y * y));
	}

	void Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
	}
	Vector2 GetNormalized() const
	{
		float length = Length();
		return Vector2(x / length, y / length);
	}

	float Angle()const
	{
		return atan2(y,x);
	}

};
