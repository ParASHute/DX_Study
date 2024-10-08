#pragma once

#include "Skeleton/AnimationRect.h"
#include "Item/Item.h"

enum class MonsterType {
	BlueSmlime = 0,
	PurpleSlime,
	Orc,
	Skeleton,
	Boss
};

class Monster{
public:
	Monster(Vector3 position, Vector3 size, MonsterType type, float rotation = 0.0f);
	Monster(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Monster();

	void Update();
	void Render();
	void Move();
	void Attack();

	// ImGui
	void GUI();
	string MakeLable(string lable);

	// 게터 & 세터
	Vector3 GetPos() { return position; }
	void SetPos(Vector3 position) { this->position = position; }

	void SetMonsterType();

	float GetHP() { return Hp; }
	void SetHp(float Hp) { this->Hp = Hp; }

	float GetMaxHp() { return MaxHp; }
	void SetMaxHP(float MaxHp) { this->MaxHp = MaxHp; }

	BoundingBox* GetCollision() { return body->GetCollision(); }

	// 기능
	void MakeAni();

private:
	MonsterType type;

	// 구성 변수
	float Hp;
	float MaxHp = 3;
	int Def = 5;
	int Att = 0;
	int MoveSpd = 100;
	Heart* DropItem1;
	Rooby* DropItem2;

	// 트리거
	bool bDef = true;
	bool bOpen = true; // ImGui 오픈용 트리거

	// 움직임 제어용 트리거들
	bool moveU = false;	// 위로 움직이는지
	bool moveD = false; // 아래로 움직이는지
	bool moveR = false; // 오른쪽으로 움직이는지
	bool moveL = false; // 왼쪽으로 이동하는지

	//bool moveU = false; // 점프 중인지
	//bool G = true; // 중력 구현

	// 게터 & 세터용
	Vector3 position;
	Vector3 size;

	// 몸통 (에니매이션)
	AnimationRect* body;
};