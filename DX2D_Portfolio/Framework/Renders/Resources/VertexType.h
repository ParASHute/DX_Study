#pragma once

// 버택스 정보를 저장하기 위한 구조체

struct VertexColor
{
	VertexColor()
		: position(0, 0, 0), color(0, 0, 0, 0) {}

	VertexColor(Vector3 position, Color color)
		: position(position), color(color) {}

	// 정점의 위치
	Vector3 position;
	// 정점의 색상
	Color color;

	// 정점 데이터 구조를 서술
	static D3D11_INPUT_ELEMENT_DESC descs[];
	// 원소 개수
	static const uint count = 2;
};

struct VertexTexture
{
	VertexTexture()
		: position(0, 0, 0), uv(0, 0) {}

	VertexTexture(Vector3 position, Vector2 uv)
		: position(position), uv(uv) {}

	// 정점의 위치
	Vector3 position;
	// 텍스쳐 좌표
	Vector2 uv;

	// 정점 데이터 구조를 서술
	static D3D11_INPUT_ELEMENT_DESC descs[];
	// 원소 개수
	static const uint count = 2;
};

struct VertexTile
{
	VertexTile()
		: position(Values::ZeroVec3),
		uv(Values::ZeroVec2),
		color(0, 0, 0, 0) {}

	VertexTile(Vector3 position, Vector2 uv, Vector2 uv2,
		Color color, uint index)
		: position(position), uv(uv), uv2(uv2),
		color(color), index(index)
	{}

	Vector3 position;
	Vector2 uv;
	Vector2 uv2;
	Color color;
	uint index;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 5;
};