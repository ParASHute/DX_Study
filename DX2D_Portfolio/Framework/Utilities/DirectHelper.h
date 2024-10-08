#pragma once

// 필요한 부분들 디파인해둔 클라스라고 생각하면됨

class Values
{
public:
	const static float PI;

	const static Vector3 ZeroVec3;
	const static Vector3 OneVec3;
	const static Vector3 LeftVec;
	const static Vector3 RightVec;
	const static Vector3 UpVec;
	const static Vector3 DownVec;
	const static Vector3 FwdVec;
	const static Vector3 ScreenSize;

	const static Vector2 ZeroVec2;
	const static Vector2 OneVec2;
	const static Vector2 uvLT;
	const static Vector2 uvLB;
	const static Vector2 uvRT;
	const static Vector2 uvRB;

	const static Color Red;
	const static Color Green;
	const static Color Blue;
	const static Color Magenta;
	const static Color Black;
	const static Color White;
	const static Color ClearColor;

	const static Matrix Identity;
};

// 행렬 연산 srt연산
class DXMath
{
public:
	static Matrix Translation(const Vector3& position)
	{
		Matrix m;
		D3DXMatrixTranslation(&m, position.x, position.y, position.z);
		return m;
	}

	static Matrix Translation(const float& x, const float& y, const float& z)
	{
		return Translation(Vector3(x, y, z));
	}

	static Matrix TranslationX(const float& x)
	{
		return Translation(x, 0, 0);
	}

	static Matrix TranslationY(const float& y)
	{
		return Translation(0, y, 0);
	}

	static Matrix TranslationZ(const float& z)
	{
		return Translation(0, 0, z);
	}

	static Matrix Scaling(const Vector3& size)
	{
		Matrix m;
		D3DXMatrixScaling(&m, size.x, size.y, size.z);
		return m;
	}

	static Matrix Scaling(const float& x, const float& y, const float& z)
	{
		Matrix m;
		D3DXMatrixScaling(&m, x, y, z);
	}

	static Matrix ScalingX(const float& x)
	{
		return Scaling(x, 1, 1);
	}

	static Matrix ScalingY(const float& y)
	{
		return Scaling(1, y, 1);
	}

	static Matrix ScalingZ(const float& z)
	{
		return Scaling(1, 1, z);
	}

	static Matrix RotationInDegree(const float& rotation)
	{
		Matrix m;
		D3DXMatrixRotationZ(&m, (float)D3DXToRadian(rotation));
		return m;
	}

	static Matrix RotationInRadian(const float& rotation)
	{
		Matrix m;
		D3DXMatrixRotationZ(&m, rotation);
		return m;
	}
};