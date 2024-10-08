#pragma once

#include "../../GameSources/Classes/Player.h"
#include "../../GameSources/Classes/Item/Item.h"
#include "../../GameSources/Classes/Item/SpecialItem.h"

class ItemManager : public SingletonBase<ItemManager> {
public:
	friend class SingletonBase<ItemManager>;

private:
	ItemManager(Player* player,Arrow* arrow, Bomb* bomb, Heart* heart, Rooby* rooby, Sowrd* sowrd, HeartPlate* heartPlate, Bow* bow, BombPorket* bombPorket);
	~ItemManager();

	//Items
	void SetArrow();
	void SetBomb();
	void SetHeart();
	void SetRooby();

	//SpecialItems
	void SetSword();
	void SetHearPlate();
	void SetBow();
	void SetBombPorket();

	void SetBombPortketCount();
	void SetBowcount();

	Sowrd* GetSowrd() { return sowrd; }
	HeartPlate* GetHeartPlate() { return heartPlate; }
	Bow* GetBow() { return bow; }
	BombPorket* GetBombPorket() { return bombPorket; }

private:
	Player* player = nullptr;

	//Items
	Arrow* arrow = nullptr;
	Bomb* bomb = nullptr;
	Heart* heart = nullptr;
	Rooby* rooby = nullptr;

	//SpecialItems
	Sowrd* sowrd = nullptr;
	HeartPlate* heartPlate = nullptr;
	Bow* bow = nullptr;
	BombPorket* bombPorket = nullptr;
};