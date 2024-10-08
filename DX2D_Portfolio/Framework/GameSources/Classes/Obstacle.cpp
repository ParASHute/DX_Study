#include "Framework.h"
#include "Obstacle.h"

Obstacle::Obstacle(Vector3 position, Vector3 size, float rotation)
{
	obstacle = new Rect(position, size);
	obstacle->SetColor(color);
}

Obstacle::~Obstacle()
{
	SAFE_DELETE(obstacle);
}