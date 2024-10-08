#include "Framework.h"
#include "ItemManager.h"

ItemManager::ItemManager(Player* player, Arrow* arrow, Bomb* bomb, Heart* heart, Rooby* rooby, Sowrd* sowrd, HeartPlate* heartPlate, Bow* bow, BombPorket* bombPorket)
{
	// Player
	this->player = player;

	// Itmes
	this->arrow = arrow;
	this->bomb = bomb;
	this->heart = heart;
	this->rooby = rooby;

	// SpecialItems
	this->sowrd = sowrd;
	this->heartPlate = heartPlate;
	this->bow = bow;
	this->bombPorket = bombPorket;
}

ItemManager::~ItemManager()
{
	// Player
	SAFE_DELETE(player);
	
	// Items
	SAFE_DELETE(arrow);
	SAFE_DELETE(bomb);
	SAFE_DELETE(heart);
	SAFE_DELETE(rooby);

	// SpecialItems
	SAFE_DELETE(sowrd);
	SAFE_DELETE(heartPlate);
	SAFE_DELETE(bow);
	SAFE_DELETE(bombPorket);
}

void ItemManager::SetArrow()
{
	if (BoundingBox::AABB(player->GetCollision(), arrow->GetCollision())) {
		arrow->SetCount(arrow->GetCount() + 1);
	}
}

void ItemManager::SetBomb()
{
	if (BoundingBox::AABB(player->GetCollision(), bomb->GetCollision())) {
		bomb->SetCount(arrow->GetCount() + 1);
	}
}

void ItemManager::SetHeart()
{
	if (BoundingBox::AABB(player->GetCollision(), heart->GetCollision())) {
		if (player->GetHP() + 1 < player->GetMaxHp()) {
			player->SetHp(player->GetHP() + 1);
		}

		else if (player->GetHP() + 1 > player->GetMaxHp()) {
			player->SetHp(player->GetMaxHp());
		}
	}
}

void ItemManager::SetRooby()
{
	if (BoundingBox::AABB(player->GetCollision(), rooby->GetCollision())) {
		rooby->SetCount(arrow->GetCount() + 1);
	}
}

void ItemManager::SetSword()
{
	if (BoundingBox::AABB(player->GetCollision(), sowrd->GetCollision())) {
		sowrd->SetPossessSowrd(true);
		if (sowrd->GetPossessSowrd() == true) {
			player->SetCanAtt(true);
		}
	}
}

void ItemManager::SetHearPlate()
{
	if (BoundingBox::AABB(player->GetCollision(), heartPlate->GetCollision())) {
		player->SetMaxHP(player->GetMaxHp() + 1);
	}
}

void ItemManager::SetBow()
{
	if (BoundingBox::AABB(player->GetCollision(), bow->GetCollision())) {
		bow->SetUsavble(true);
	}
}

void ItemManager::SetBombPorket()
{
	if (BoundingBox::AABB(player->GetCollision(), bombPorket->GetCollision())) {
		bombPorket->SetUsable(true);
	}
}