#pragma once

#include "Skeleton/Rect.h"

#include "Skeleton/AnimationRect.h"
#include "Inventory/Inventory.h"

class Player {
public:
	// 생성자 & 소멸자
	Player(Vector3 position, Vector3 size, float rotation = 0.0f);
	~Player();

	// 구성함수 
	void Update();
	void Render();
	void Move();

	// ImGui
	void GUI();
	string MakeLable(string lable);

	// 게터 & 세터
	void SetAni(AnimType type);
	void SetType(AnimType type) { this->type = type; }

	Vector3 GetPos() { return position; }
	void SetPos(Vector3 position) { this->position = position; }
	
	float GetHP() { return Hp; }
	void SetHp(float Hp) { this->Hp = Hp; }

	int GetMaxHp() { return MaxHp; }
	void SetMaxHP(float MaxHp) { this->MaxHp = MaxHp; }

	bool GetStay() { return bStay; }
	void setStay(int y, int x); 

	void SetCanAtt(bool canAtt) { this->canAtt = canAtt; }

	BoundingBox* GetCollision() { return body->GetCollision() ; }

	AnimationRect* GetAttMotion() { return attMotion; }

	AnimType GetAnimType() { return type; }

	bool GetAttTrigger() { return bAtt; }
	bool GetEquipmentSword() { return equipmentSword; }
	bool GetDefenceTrigger() { return bDef; }

	float GetSwordRange() { return swordRange; }
	
	/*
	bool GetMoveL() { return moveL; }
	*/

private:
	// 구성 변수
	float Hp = 3;
	int MaxHp =3;
	int Def = 5;
	int Att = 0;
	int MoveSpd = 100;
	Inventory* inven;

	// 트리거
	bool canAtt = false;
	bool equipmentSword = false;
	bool bDef = true;
	bool bAtt = false;
	bool bOpen = true; // ImGui 오픈용 트리거

	// 움직임 제어용 트리거들
	bool moveU = false;	// 위로 움직이는지
	bool moveD = false; // 아래로 움직이는지
	bool moveR = false; // 오른쪽으로 움직이는지
	bool moveL = false; // 왼쪽으로 이동하는지

	// 위치 트리거
	bool bStay[4][4];
	bool D1 = false;
	bool D2 = false;
	bool hidden = false;

	AnimType type = AnimType::Down;

	// 게터 & 세터용
	Vector3 position;
	Vector3 size;

	// 몸통 (에니매이션)
	AnimationRect* body;

	// 예비 몸통 -> 공격 모션 + 범위
	AnimationRect* attMotion;
	float swordRange;
};