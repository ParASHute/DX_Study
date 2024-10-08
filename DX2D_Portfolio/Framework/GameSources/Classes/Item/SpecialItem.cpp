#include "Framework.h"
#include "SpecialItem.h"

Sowrd::Sowrd(Vector3 position, Vector3 size, float rotation)
{
	Image = new TextureRect(position, size, rotation);
}

Sowrd::~Sowrd()
{
	SAFE_DELETE(Image);
}



HeartPlate::HeartPlate(Vector3 position, Vector3 size, float rotation)
{
	Image = new TextureRect(position, size, rotation);
}

HeartPlate::~HeartPlate()
{
	SAFE_DELETE(Image);
}



Bow::Bow(Vector3 position, Vector3 size, float rotation)
{
	Image = new TextureRect(position, size, rotation);
}

Bow::~Bow()
{
	SAFE_DELETE(Image);
}

void Bow::SetShootArrow()
{
	if (arrowCount <= 0) {
		shootArrow = false;
		arrowCount == 0;
	}
	else shootArrow = true;
}

BombPorket::BombPorket(Vector3 position, Vector3 size, float rotation)
{
	Image = new TextureRect(position, size, rotation);
}

BombPorket::~BombPorket()
{
	SAFE_DELETE(Image);
}

void BombPorket::SetUseBomb()
{
	if (bombCount <= 0) {
		useBomb = false;
		bombCount = 0;
	}

	else useBomb = true;
}
