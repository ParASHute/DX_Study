#pragma once
#include "SystemDef.h"

//벡터 3 관련 연산자 기존엔 
//d3dx9 math 라이브러리에 기능이있었으나 xm(directX Math)뭐시기에는 사라져서 만들어줘야됨.
//directx 9에 있는거 써도 됨.
class Vector3
{
private:
	Vector4 value; //행렬 연산에 사용하므로 vector4
public:
	Vector3(Float3 value)
		:value(XMLoadFloat3(&value))
	{
	}
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
		:value(XMVectorSet(x,y,z,0))
	{
	}

	Vector3(Vector4 value) : value(value)
	{

	}

	void SetX(const float& x)
	{
		value = XMVectorSetX(value,x);
	}
	void SetY(const float& y)
	{
		value = XMVectorSetY(value, y);
	}
	void SetZ(const float& z)
	{
		value = XMVectorSetZ(value, z);
	}
	float GetX() const { return XMVectorGetX(value); }
	float GetY() const { return XMVectorGetY(value); }
	float GetZ() const { return XMVectorGetZ(value); }

	//get set property
	__declspec(property(get = GetX, put = SetX)) float x;
	__declspec(property(get = GetY, put = SetY)) float y;
	__declspec(property(get = GetZ, put = SetZ)) float z;

	operator Vector4() { return value; }

	operator Float3()
	{
		Float3 result;
		XMStoreFloat3(&result, value);
		return result;
	}
	//연산자 오버로딩
	Vector3 operator+(const Vector3& v) const { return value + v.value; }
	Vector3 operator-(const Vector3& v) const { return value - v.value; }

	Vector3 operator*(const float& s) const { return value * s; }
	Vector3 operator/(const float& s) const { return value / s; }

	void operator*=(const float& s) { value *= s; }
	void operator/=(const float& s) { value /= s; }

	void operator+=(const Vector3& v) { value += v.value; }
	void operator-=(const Vector3& v) { value -= v.value; }



	friend void operator+=(Float3& v1, const Vector3& v2)
	{
		Vector4 temp = XMLoadFloat3(&v1) + v2.value;
		XMStoreFloat3(&v1, temp);
	}
	friend void operator-=(Float3& v1, const Vector3& v2)
	{
		Vector4 temp = XMLoadFloat3(&v1) - v2.value;
		XMStoreFloat3(&v1, temp);
	}

	bool operator==(const Vector3& v)
	{
		return XMVector3Equal(value, v.value);
	}
	bool operator!=(const Vector3& v)
	{
		return !XMVector3Equal(value, v.value);
	}

	float operator[](const UINT& index)const 
	{
		switch (index)
		{
			case 0: return GetX();
			case 1: return GetY();
			case 2: return GetZ();
		}
	}

	float Length() const { return XMVectorGetX(XMVector3Length(value)); }

	Vector3 GetNormalized() const { return XMVector3Normalize(value); }
	void Normalize() { value = XMVector3Normalize(value); }

	Vector4* GetValue() { return &value; }
	static Vector3 Zero() { return Vector3(); }
	static Vector3 One() { return Vector3(1.f, 1.f, 1.f); }
	static Vector3 Right() { return Vector3(1.f, 0.f, 0.f); }
	static Vector3 Left() { return Vector3(-1.f, 0.f, 0.f); }
	static Vector3 Up() { return Vector3(0.f, 1.f, 0.f); }
	static Vector3 Down() { return Vector3(0.f, -1.f, 0.f); }

	static Vector3 Forward() { return Vector3(0.f, 0.f, 1.f); }
	static Vector3 Back() { return Vector3(0.f, 0.f, -1.f); }

};

