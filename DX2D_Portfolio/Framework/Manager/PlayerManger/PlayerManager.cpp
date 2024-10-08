#include "Framework.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager(Player* player)
{
	this->player = player;
	for (int i = 0; i < 20; i++) {
		Heart[i]->SetImage(TexturePath + L"Item/Hearts_Red_1.png");
		/*
		if(i < 10) Heart[i] = new TextureRect({0 + (float)(8 * i),WinMaxHeight,0}, {16, 16, 1});
		else Heart[i] = new TextureRect({ 0 + (float)(8 * i),WinMaxHeight - 16 ,0 }, { 16, 16, 1 });
			 하트 위치 다시계산해서 넣을 것
		*/
	}
}

PlayerManager::~PlayerManager()
{
	for (int i = 19; i >= 0; i--) SAFE_DELETE(Heart[i]);
	SAFE_DELETE(player);
}

void PlayerManager::Update()
{
	for (int i = 0; i < player->GetMaxHp(); i++) Heart[i]->Update();
	player->Update();
}

void PlayerManager::Render()
{
	MakePlayerHpIndicator();
	player->Render();
}

void PlayerManager::Move(vector<Obstacle*> obstacle)
{
	int MoveSpd = 100;
	for(Obstacle* r : obstacle){
		if (BoundingBox::AABB(r->GetCollision(), player->GetCollision())) {
			if(player->GetAnimType() == AnimType::Up)
				player->SetPos({ player->GetPos().x, player->GetPos().y + MoveSpd * Time::Delta(), 0 });

			if (player->GetAnimType() == AnimType::Down) 
				player->SetPos({ player->GetPos().x, player->GetPos().y - MoveSpd * Time::Delta(), 0 });

			if (player->GetAnimType() == AnimType::Left) 
				player->SetPos({ player->GetPos().x + MoveSpd * Time::Delta(), player->GetPos().y, 0 });

			if (player->GetAnimType() == AnimType::Right)
				player->SetPos({ player->GetPos().x - MoveSpd * Time::Delta(), player->GetPos().y, 0 });
		}
	}
}

void PlayerManager::Attack(vector<Monster*> monster)
{
	for (Monster* r : monster) {
		if (BoundingBox::AABB(r->GetCollision(), player->GetAttMotion()->GetCollision())) {
			if (player->GetAttTrigger() == true) {
				
			}
		}
	}
	
}

void PlayerManager::Defence(vector<Monster*> monster)
{
	for (Monster* r : monster) {
		if (BoundingBox::AABB(r->GetCollision(), player->GetAttMotion()->GetCollision())) {
			if (player->GetDefenceTrigger() == true) {

			}
		}
	}
}

void PlayerManager::MakePlayerHpIndicator()
{
	float length = player->GetMaxHp() - player->GetHP();
	int count = 0;
	for (int i = 0; i < 20; i++) {
		if (1 > length && length > 0) {
			// Hp가 N.75인 상황
			if (1 > length && length - 0.25f > 0) {
				Heart[count]->SetImage(TexturePath + L"");
			}

			// Hp가 N.5인 상황
			else if (1 > length && length - 0.5f > 0) {
				Heart[count]->SetImage(TexturePath + L"");
			}

			// Hp가 N.25인 상황
			else if (1 > length && length - 0.75f > 0) {
				Heart[count]->SetImage(TexturePath + L"");
			}

			break;
		}

		else {
			length--;
			count++;
		}
	}
}