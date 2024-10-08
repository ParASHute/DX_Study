#pragma once

#include "../../GameSources/Classes/Player.h"
#include "../../GameSources/Classes/Obstacle.h"
#include "../../GameSources/Classes/Monster.h"
#include "../../GameSources/Classes/Inventory/Inventory.h"

class PlayerManager : public SingletonBase<PlayerManager> {
public:
	friend SingletonBase<PlayerManager>;

private:
	PlayerManager(Player* player);
	~PlayerManager();

	void Update();
	void Render();

	void Move(vector<Obstacle*> obstacle);
	void Attack(vector<Monster*> monster);
	void Defence(vector<Monster*> monster);

	void MakePlayerHpIndicator();

private:
	Player* player = nullptr;

	TextureRect* Heart[20] = { nullptr, };
};