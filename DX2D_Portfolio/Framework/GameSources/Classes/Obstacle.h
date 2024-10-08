#pragma once

#include "Skeleton/Rect.h"

class Obstacle {
public:
	Obstacle(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Obstacle();

	BoundingBox* GetCollision() { return obstacle->GetCollision(); }
private:
	Rect* obstacle;

	Color color = Color(1, 1, 1, 0);
};