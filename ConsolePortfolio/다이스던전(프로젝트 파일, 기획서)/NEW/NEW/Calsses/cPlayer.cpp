#include "cPlayer.h"

cPlayer::cPlayer(cPlayer& player) {
	this->Name = player.Name;
	this->pState = player.pState;
}

HollyKnight::HollyKnight() : cPlayer() { }
HollyKnight::~HollyKnight() { }
void HollyKnight::SetState() {
	this->pState.Tag = "HollyKnight";
	this->pState.Hp = this->maxState.Hp;
	this->pState.Mp = this->maxState.Mp;
	this->pState.ad = this->maxState.ad;
	this->pState.ap = this->maxState.ap;
	this->pState.adDef = this->maxState.adDef;
	this->pState.apDef = this->maxState.apDef;
	this->pState.speed = 1;
}
void HollyKnight::SetMaxState() {
	this->maxState.Hp = 200;
	this->maxState.Mp = 100;
	this->maxState.ad = 10;
	this->maxState.ap = 10;
	this->maxState.adDef = 25;
	this->maxState.apDef = 25;
	this->maxState.MaxEXP = 100;
}
void HollyKnight::SetLevel() {
	if (this->EXP == this->maxState.MaxEXP) {
		Level++;
		this->EXP = 0;
		this->maxState.Hp += 15;
		this->maxState.Mp += 10;
		this->maxState.ad += 5;
		this->maxState.ap += 5;
		this->maxState.adDef += 10;
		this->maxState.apDef += 10;
		this->maxState.MaxEXP += 50;
	}
}
void HollyKnight::SetExp(int Exp){
	this->EXP += Exp;
}
void HollyKnight::SetAdDeffence(int addeff) {
	this->Def.adDef += addeff;
}
void HollyKnight::SetApDeffence(int apdeff) {
	this->Def.apDef += apdeff;
}
void HollyKnight::GoHotel(int Hp, int Mp) {
	this->pState.Hp = Hp;
	this->pState.Mp = Mp;
}
void HollyKnight::UseSkill() {
	this->pState.Mp -= 10;
}
void HollyKnight::Skill_1() {
	this->SkillName_1 = "다바인 스윙";
}
void HollyKnight::Skill_2() {
	this->SkillName_2 = "디바인 차지";
}
void HollyKnight::Skill_3() {
	this->SkillName_3 = "쉴드 마스터리";
}
void HollyKnight::Skill_4() {
	this->SkillName_4 = "매직 크래쉬";
}


Worrier::Worrier() : cPlayer() { }
Worrier::~Worrier() { }
void Worrier::SetState() {
	this->pState.Tag = "Worrier";
	this->pState.Hp = this->maxState.Hp;
	this->pState.Mp = this->maxState.Mp;
	this->pState.ad = this->maxState.ad;
	this->pState.ap = this->maxState.ap;
	this->pState.adDef = this->maxState.adDef;
	this->pState.apDef = this->maxState.apDef;
	this->pState.speed = 4;
}
void Worrier::SetMaxState() {
	this->maxState.Hp = 150;
	this->maxState.Mp = 100;
	this->maxState.ad = 15;
	this->maxState.ap = 10;
	this->maxState.adDef = 20;
	this->maxState.apDef = 20;
	this->maxState.MaxEXP = 100;
}
void Worrier::SetLevel() {
	if (this->EXP == this->maxState.MaxEXP) {
		Level++;
		this->EXP = 0;
		this->maxState.Hp += 15;
		this->maxState.Mp += 10;
		this->maxState.ad += 10;
		this->maxState.ap += 10;
		this->maxState.adDef += 5;
		this->maxState.apDef += 5;
		this->maxState.MaxEXP += 50;
	}
}
void Worrier::SetExp(int Exp) {
	this->EXP += Exp;
}
void Worrier::SetAdDeffence(int addeff) {
	this->Def.adDef += addeff;
}
void Worrier::SetApDeffence(int apdeff) {
	this->Def.apDef += apdeff;
}
void Worrier::GoHotel(int Hp, int Mp) {
	this->pState.Hp = Hp;
	this->pState.Mp = Mp;
}
void Worrier::UseSkill() {
	this->pState.Mp -= 10;
}
void Worrier::Skill_1() {
	this->SkillName_1 = "플래시 슬래시";
}
void Worrier::Skill_2() {
	this->SkillName_2 = "브래이브 슬래시";
}
void Worrier::Skill_3() {
	this->SkillName_3 = "셀프 리커버리";
}
void Worrier::Skill_4() {
	this->SkillName_4 = "인듀어";
}


Maige::Maige() : cPlayer() { }
Maige::~Maige() { }
void Maige::SetState() {
	this->pState.Tag = "Maige";
	this->pState.Hp = this->maxState.Hp;
	this->pState.Mp = this->maxState.Mp;
	this->pState.ad = this->maxState.ad;
	this->pState.ap = this->maxState.ap;
	this->pState.adDef = this->maxState.adDef;
	this->pState.apDef = this->maxState.apDef;
	this->pState.speed = 3;
}
void Maige::SetMaxState() {
	this->maxState.Hp = 100;
	this->maxState.Mp = 250;
	this->maxState.ad = 10;
	this->maxState.ap = 15;
	this->maxState.adDef = 10;
	this->maxState.apDef = 15;
	this->maxState.MaxEXP = 100;
}
void Maige::SetLevel() {
	if (this->EXP == this->maxState.MaxEXP) {
		Level++;
		this->EXP = 0;
		this->maxState.Hp += 10;
		this->maxState.Mp += 15;
		this->maxState.ad += 5;
		this->maxState.ap += 10;
		this->maxState.adDef += 5;
		this->maxState.apDef += 10;
		this->maxState.MaxEXP += 50;
	}
}
void Maige::SetExp(int Exp) {
	this->EXP += Exp;
}
void Maige::SetAdDeffence(int addeff) {
	this->Def.adDef += addeff;
}
void Maige::SetApDeffence(int apdeff) {
	this->Def.apDef += apdeff;
}
void Maige::GoHotel(int Hp, int Mp) {
	this->pState.Hp = Hp;
	this->pState.Mp = Mp;
}
void Maige::UseSkill() {
	this->pState.Mp -= 10;
}
void Maige::Skill_1() {
	this->SkillName_1 = "에너지 볼트";
}
void Maige::Skill_2() {
	this->SkillName_2 = "빅뱅";
}
void Maige::Skill_3() {
	this->SkillName_3 = "매직 아머";
}
void Maige::Skill_4() {
	this->SkillName_4 = "매직 가드";
}


Cleric::Cleric() : cPlayer() { }
Cleric::~Cleric() { }
void Cleric::SetState() {
	this->pState.Tag = "Cleric";
	this->pState.Hp = maxState.Hp;
	this->pState.Mp = maxState.Mp;
	this->pState.ad = maxState.ad;
	this->pState.ap = maxState.ap;
	this->pState.adDef = maxState.adDef;
	this->pState.apDef = maxState.apDef;
	this->pState.speed = 2;
}
void Cleric::SetMaxState() {
	this->maxState.Hp = 100;
	this->maxState.Mp = 150;
	this->maxState.ad = 10;
	this->maxState.ap = 10;
	this->maxState.adDef = 10;
	this->maxState.apDef = 10;
	this->maxState.MaxEXP = 100;
}
void Cleric::SetLevel() {
	if (this->EXP == this->maxState.MaxEXP) {
		Level++;
		this->EXP = 0;
		this->maxState.Hp += 10;
		this->maxState.Mp += 10;
		this->maxState.ad += 10;
		this->maxState.ap += 10;
		this->maxState.adDef += 5;
		this->maxState.apDef += 10;
		this->maxState.MaxEXP += 50;
	}
}
void Cleric::SetExp(int Exp) {
	this->EXP += Exp;
}
void Cleric::SetAdDeffence(int addeff) {
	this->Def.adDef += addeff;
}
void Cleric::SetApDeffence(int apdeff) {
	this->Def.apDef += apdeff;
}
void Cleric::GoHotel(int Hp, int Mp) {
	this->pState.Hp = Hp;
	this->pState.Mp = Mp;
}
void Cleric::UseSkill(){
	this->pState.Mp -= 10;
}
void Cleric::Skill_1()  {
	this->SkillName_1 = "홀리 에로우";
}
void Cleric::Skill_2() {
	this->SkillName_2 = "블레스";
}
void Cleric::Skill_3() {
	this->SkillName_3 = "홀리 포커스";
}
void Cleric::Skill_4() {
	this->SkillName_4 = "홀리 매직쉘";
}