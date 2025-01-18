#include "cMonster.h"

cMonster::cMonster(cMonster& monster) {
	this->MonName = monster.MonName;
	this->MonState = monster.MonState;
}

// 1스테이지
Slime::Slime() : cMonster() { }
Slime::~Slime() { }
void Slime::SetMonState() {
	this->MonState.Hp = 50;
	this->MonState.Mp = 45;
	this->MonState.ad = 5;
	this->MonState.ap = 5;
	this->MonState.adDef = 5;
	this->MonState.apDef = 5;
	this->MonState.EXP = 50;
}
void Slime::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Slime::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Slime::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Slime::SetBleedTurn(){
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Slime::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Slime::SetSturnTurn(){
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Slime::SetTunt(int turn){
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Slime::SetTuntTurn(){
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Slime::Skill_1() {
	this->SkillName_1 = "탄성 주먹";
}
void Slime::Skill_2() {
	this->SkillName_2 = "불안정한 물질";
}
void Slime::Skill_3() {
	this->SkillName_3 = "새총발사";
}
void Slime::Skill_4() {
	this->SkillName_4 = "바운스!";
}

Gobllin::Gobllin() : cMonster() { } 
Gobllin::~Gobllin() { }
void Gobllin::SetMonState() {
	this->MonState.Hp = 55;
	this->MonState.Mp = 50;
	this->MonState.ad = 2;
	this->MonState.ap = 2;
	this->MonState.adDef = 2;
	this->MonState.apDef = 2;
	this->MonState.EXP = 55;
}
void Gobllin::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Gobllin::SetBurnTurn(){
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Gobllin::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Gobllin::SetBleedTurn(){
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Gobllin::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Gobllin::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Gobllin::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Gobllin::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Gobllin::Skill_1() {
	this->SkillName_1 = "부메랑 던지기";
}
void Gobllin::Skill_2() {
	this->SkillName_2 = "슝슝";
}
void Gobllin::Skill_3() {
	this->SkillName_3 = "폴짝";
}
void Gobllin::Skill_4() {
	this->SkillName_4 = "깨물기";
}

Kobold::Kobold() : cMonster() { }
Kobold::~Kobold() { }
void Kobold::SetMonState() {
	this->MonState.Hp = 60;
	this->MonState.Mp = 55;
	this->MonState.ad = 4;
	this->MonState.ap = 4;
	this->MonState.adDef = 4;
	this->MonState.apDef = 4;
	this->MonState.EXP = 60;
}
void Kobold::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Kobold::SetBurnTurn() {
	if(burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Kobold::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Kobold::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Kobold::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Kobold::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Kobold::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Kobold::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Kobold::Skill_1() {
	this->SkillName_1 = "돌덩이 던지기";
}
void Kobold::Skill_2() {
	this->SkillName_2 = "쿵쾅";
}
void Kobold::Skill_3() {
	this->SkillName_3 = "우지끈";
}
void Kobold::Skill_4() {
	this->SkillName_4 = "밀치기";
}

LizardMan::LizardMan() : cMonster() { }
LizardMan::~LizardMan() { }
void LizardMan::SetMonState() {
	this->MonState.Hp = 65;
	this->MonState.Mp = 60;
	this->MonState.ad = 6;
	this->MonState.ap = 6;
	this->MonState.adDef = 6;
	this->MonState.apDef = 6;
	this->MonState.EXP = 65;
}
void LizardMan::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void LizardMan::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void LizardMan::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void LizardMan::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void LizardMan::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void LizardMan::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void LizardMan::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void LizardMan::SetTuntTurn()  {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void LizardMan::Skill_1() {
	this->SkillName_1 = "양떼 도륙";
}
void LizardMan::Skill_2() {
	this->SkillName_2 = "무자비한 포식자";
}
void LizardMan::Skill_3() {
	this->SkillName_3 = "자르고 토막내기";
}
void LizardMan::Skill_4() {
	this->SkillName_4 = "강신";
}

// 2스테이지
Scorpion::Scorpion() : cMonster() { }
Scorpion::~Scorpion() { }
void Scorpion::SetMonState() {
	this->MonState.Hp = 70;
	this->MonState.Mp = 65;
	this->MonState.ad = 8;
	this->MonState.ap = 8;
	this->MonState.adDef = 8;
	this->MonState.apDef = 8;
	this->MonState.EXP = 70;
}
void Scorpion::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Scorpion::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Scorpion::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Scorpion::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Scorpion::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Scorpion::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Scorpion::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Scorpion::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Scorpion::Skill_1() {
	this->SkillName_1 = "수정베기";
}
void Scorpion::Skill_2() {
	this->SkillName_2 = "수정 외골격";
}
void Scorpion::Skill_3() {
	this->SkillName_3 = "균열 내기";
}
void Scorpion::Skill_4() {
	this->SkillName_4 = "꿰뚫기";
}

Mummy::Mummy() : cMonster(){ }
Mummy::~Mummy() { }
void Mummy::SetMonState() {
	this->MonState.Hp = 75;
	this->MonState.Mp = 70;
	this->MonState.ad = 10;
	this->MonState.ap = 10;
	this->MonState.adDef = 10;
	this->MonState.apDef = 10;
	this->MonState.EXP = 75;
}
void Mummy::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Mummy::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Mummy::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Mummy::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Mummy::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Mummy::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Mummy::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Mummy::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Mummy::Skill_1() {
	this->SkillName_1 = "저주의 손길";
}
void Mummy::Skill_2() {
	this->SkillName_2 = "븅대 던지기";
}
void Mummy::Skill_3() {
	this->SkillName_3 = "짜증내기";
}
void Mummy::Skill_4() {
	this->SkillName_4 = "슬픈 미라의 저주";
}

Mimmic::Mimmic() : cMonster() { }
Mimmic::~Mimmic() { }
void Mimmic::SetMonState() {
	this->MonState.Hp = 80;
	this->MonState.Mp = 75;
	this->MonState.ad = 12;
	this->MonState.ap = 12;
	this->MonState.adDef = 12;
	this->MonState.apDef = 12;
	this->MonState.EXP = 80;
}
void Mimmic::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Mimmic::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Mimmic::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Mimmic::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Mimmic::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Mimmic::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Mimmic::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Mimmic::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Mimmic::Skill_1() {
	this->SkillName_1 = "깨물기";
}
void Mimmic::Skill_2() {
	this->SkillName_2 = "삼키기";
}
void Mimmic::Skill_3() {
	this->SkillName_3 = "덮치기";
}
void Mimmic::Skill_4() {
	this->SkillName_4 = "해골 던지기";
}

Sandman::Sandman() : cMonster() { }
Sandman::~Sandman() { }
void Sandman::SetMonState() {
	this->MonState.Hp = 85;
	this->MonState.Mp = 80;
	this->MonState.ad = 14;
	this->MonState.ap = 14;
	this->MonState.adDef = 14;
	this->MonState.apDef = 14;
	this->MonState.EXP = 85;
}
void Sandman::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Sandman::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Sandman::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Sandman::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Sandman::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Sandman::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Sandman::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Sandman::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Sandman::Skill_1() {
	this->SkillName_1 = "사막의 맹습";
}
void Sandman::Skill_2() {
	this->SkillName_2 = "영혼의 포식자";
}
void Sandman::Skill_3() {
	this->SkillName_3 = "영혼의 불길";
}
void Sandman::Skill_4() {
	this->SkillName_4 = "사막의 분노";
}

// 3스테이지
Skeleton::Skeleton() : cMonster() { }
Skeleton::~Skeleton() { }
void Skeleton::SetMonState() {
	this->MonState.Hp = 90;
	this->MonState.Mp = 85;
	this->MonState.ad = 16;
	this->MonState.ap = 16;
	this->MonState.adDef = 16;
	this->MonState.apDef = 16;
	this->MonState.EXP = 85;
}
void Skeleton::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Skeleton::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Skeleton::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Skeleton::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Skeleton::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Skeleton::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Skeleton::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Skeleton::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Skeleton::Skill_1() {
	this->SkillName_1 = "팔뼈 휘두르기";
}
void Skeleton::Skill_2() {
	this->SkillName_2 = "갈비뼈 던지기";
}
void Skeleton::Skill_3() {
	this->SkillName_3 = "뼈 작살";
}
void Skeleton::Skill_4(){
	this->SkillName_4 = "뺘무리의 부름";
}

Zombie::Zombie() : cMonster() { }
Zombie::~Zombie() { }
void Zombie::SetMonState() {
	this->MonState.Hp = 95;
	this->MonState.Mp = 90;
	this->MonState.ad = 18;
	this->MonState.ap = 18;
	this->MonState.adDef = 18;
	this->MonState.apDef = 18;
	this->MonState.EXP = 90;
}
void Zombie::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Zombie::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Zombie::SetBleed(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Zombie::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Zombie::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Zombie::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Zombie::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Zombie::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Zombie::Skill_1() {
	this->SkillName_1 = "죽음의 손아귀";
}
void Zombie::Skill_2() {
	this->SkillName_2 = "사형 선고";
}
void Zombie::Skill_3() {
	this->SkillName_3 = "부식성 침";
}
void Zombie::Skill_4() {
	this->SkillName_4 = "사막의 맹습";
}

Wraith::Wraith() : cMonster() { }
Wraith::~Wraith() { }
void Wraith::SetMonState() {
	this->MonState.Hp = 100;
	this->MonState.Mp = 95;
	this->MonState.ad = 20;
	this->MonState.ap = 20;
	this->MonState.adDef = 20;
	this->MonState.apDef = 20;
	this->MonState.EXP = 95;
}
void Wraith::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Wraith::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Wraith::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Wraith::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Wraith::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Wraith::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Wraith::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Wraith::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Wraith::Skill_1() {
	this->SkillName_1 = "악의 장막";
}
void Wraith::Skill_2() {
	this->SkillName_2 = "증오의 가시";
}
void Wraith::Skill_3() {
	this->SkillName_3 = "황홀한 저주";
}
void Wraith::Skill_4() {
	this->SkillName_4 = "최후의 포옹";
}

Gagotle::Gagotle() : cMonster() { }
Gagotle::~Gagotle() { }
void Gagotle::SetMonState() {
	this->MonState.Hp = 105;
	this->MonState.Mp = 100;
	this->MonState.ad = 22;
	this->MonState.ap = 22;
	this->MonState.adDef = 22;
	this->MonState.apDef = 22;
	this->MonState.EXP = 100;
}
void Gagotle::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Gagotle::SetBurnTurn(){
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Gagotle::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Gagotle::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Gagotle::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Gagotle::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Gagotle::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Gagotle::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Gagotle::Skill_1() {
	this->SkillName_1 = "석상의 강타";
}
void Gagotle::Skill_2() {
	this->SkillName_2 = "죽음의 돌풍";
}
void Gagotle::Skill_3() {
	this->SkillName_3 = "죽음의 주먹";
}
void Gagotle::Skill_4() {
	this->SkillName_4 = "죽음 출현";
}

// 4스테이지
Yeti::Yeti() : cMonster() { }
Yeti::~Yeti() { }
void Yeti::SetMonState() {
	this->MonState.Hp = 110;
	this->MonState.Mp = 105;
	this->MonState.ad = 24;
	this->MonState.ap = 24;
	this->MonState.adDef = 24;
	this->MonState.apDef = 24;
	this->MonState.EXP = 105;
}
void Yeti::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Yeti::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Yeti::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Yeti::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Yeti::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Yeti::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Yeti::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Yeti::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Yeti::Skill_1() {
	this->SkillName_1 = "눈덩이 던지기";
}
void Yeti::Skill_2() {
	this->SkillName_2 = "눈덩이 굴리기";
}
void Yeti::Skill_3() {
	this->SkillName_3 = "잡아먹기";
}
void Yeti::Skill_4() {
	this->SkillName_4 = "절대영도";
}

Gorlem::Gorlem() : cMonster() { }
Gorlem::~Gorlem() { }
void Gorlem::SetMonState() {
	this->MonState.Hp = 115;
	this->MonState.Mp = 110;
	this->MonState.ad = 26;
	this->MonState.ap = 26;
	this->MonState.adDef = 26;
	this->MonState.apDef = 26;
	this->MonState.EXP = 110;
}
void Gorlem::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Gorlem::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Gorlem::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Gorlem::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Gorlem::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Gorlem::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Gorlem::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Gorlem::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Gorlem::Skill_1() {
	this->SkillName_1 = "얼음 파편 던지기";
}
void Gorlem::Skill_2() {
	this->SkillName_2 = "얼음 갈퀴";
}
void Gorlem::Skill_3() {
	this->SkillName_3 = "서리 폭팔";
}
void Gorlem::Skill_4() {
	this->SkillName_4 = "얼음 무덤";
}

WereWolve::WereWolve() : cMonster(){ }
WereWolve::~WereWolve(){ }
void WereWolve::SetMonState() {
	this->MonState.Hp = 120;
	this->MonState.Mp = 115;
	this->MonState.ad = 28;
	this->MonState.ap = 28;
	this->MonState.adDef = 28;
	this->MonState.apDef = 28;
	this->MonState.EXP = 115;
}
void WereWolve::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void WereWolve::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void WereWolve::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void WereWolve::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void WereWolve::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void WereWolve::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void WereWolve::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void WereWolve::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void WereWolve::Skill_1() {
	this->SkillName_1 = "야수의 송곳니";
}
void WereWolve::Skill_2() {
	this->SkillName_2 = "피의 사냥";
}
void WereWolve::Skill_3() {
	this->SkillName_3 = "원시의 포효";
}
void WereWolve::Skill_4()  {
	this->SkillName_4 = "무한의 구속";
}

Griffon::Griffon() : cMonster() { }
Griffon::~Griffon() { }
void Griffon::SetMonState() {
	this->MonState.Hp = 125;
	this->MonState.Mp = 120;
	this->MonState.ad = 30;
	this->MonState.ap = 30;
	this->MonState.adDef = 30;
	this->MonState.apDef = 30;
	this->MonState.EXP = 120;
}
void Griffon::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Griffon::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Griffon::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Griffon::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Griffon::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Griffon::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Griffon::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Griffon::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Griffon::Skill_1() {
	this->SkillName_1 = "보이지 않는 위협";
}
void Griffon::Skill_2() {
	this->SkillName_2 = "공포의 깃털 날리기";
}
void Griffon::Skill_3() {
	this->SkillName_3 = "도약";
}
void Griffon::Skill_4() {
	this->SkillName_4 = "공포의 습격";
}

// 중간보스
Mandrake::Mandrake() : cMonster() { }
Mandrake::~Mandrake() { }
void Mandrake::SetMonState() {
	this->MonState.Hp = 70;
	this->MonState.Mp = 65;
	this->MonState.ad = 8;
	this->MonState.ap = 8;
	this->MonState.adDef = 8;
	this->MonState.apDef = 8;
	this->MonState.EXP = 125;
}
void Mandrake::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Mandrake::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Mandrake::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Mandrake::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Mandrake::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Mandrake::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Mandrake::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Mandrake::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Mandrake::Skill_1() {
	this->SkillName_1 = "공포의 울음";
}
void Mandrake::Skill_2() {
	this->SkillName_2 = "악취 풍기기";
}
void Mandrake::Skill_3() {
	this->SkillName_3 = "뿌리 체찍";
}
void Mandrake::Skill_4() {
	this->SkillName_4 = "나무 휘두르기";
}

Sphinx::Sphinx() : cMonster() { }
Sphinx::~Sphinx() { }
void Sphinx::SetMonState() {
	this->MonState.Hp = 90;
	this->MonState.Mp = 85;
	this->MonState.ad = 16;
	this->MonState.ap = 16;
	this->MonState.adDef = 16;
	this->MonState.apDef = 16;
	this->MonState.EXP = 130;
}
void Sphinx::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Sphinx::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Sphinx::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Sphinx::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Sphinx::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Sphinx::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Sphinx::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Sphinx::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Sphinx::Skill_1() {
	this->SkillName_1 = "칼날 바람";
}
void Sphinx::Skill_2() {
	this->SkillName_2 = "야성의 습격";
}
void Sphinx::Skill_3() {
	this->SkillName_3 = "모래 회오리";
}
void Sphinx::Skill_4() {
	this->SkillName_4 = "포식";
}

Dullahan::Dullahan() : cMonster() { }
Dullahan::~Dullahan() { }
void Dullahan::SetMonState() {
	this->MonState.Hp = 110;
	this->MonState.Mp = 105;
	this->MonState.ad = 24;
	this->MonState.ap = 24;
	this->MonState.adDef = 24;
	this->MonState.apDef = 24;
	this->MonState.EXP = 135;
}
void Dullahan::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Dullahan::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Dullahan::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Dullahan::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Dullahan::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Dullahan::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Dullahan::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Dullahan::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Dullahan::Skill_1() {
	this->SkillName_1 = "쓸어넘기기";
}
void Dullahan::Skill_2() {
	this->SkillName_2 = "쾌도난마";
} 
void Dullahan::Skill_3() {
	this->SkillName_3 = "망자의 저주";
}
void Dullahan::Skill_4() {
	this->SkillName_4 = "공포의 질주";
}

Wyvern::Wyvern() : cMonster() { }
Wyvern::~Wyvern() { }
void Wyvern::SetMonState() {
	this->MonState.Hp = 130;
	this->MonState.Mp = 125;
	this->MonState.ad = 32;
	this->MonState.ap = 32;
	this->MonState.adDef = 32;
	this->MonState.apDef = 32;
	this->MonState.EXP = 140;
}
void Wyvern::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Wyvern::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Wyvern::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Wyvern::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Wyvern::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Wyvern::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Wyvern::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Wyvern::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Wyvern::Skill_1() {
	this->SkillName_1 = "포효";
}
void Wyvern::Skill_2() {
	this->SkillName_2 = "물기";
}
void Wyvern::Skill_3() {
	this->SkillName_3 = "돌진";
}
void Wyvern::Skill_4() {
	this->SkillName_4= "써머 솔트";
}

// 보스몹
Ent::Ent() : cMonster() { }
Ent::~Ent() { }
void Ent::SetMonState() { 
	this->MonState.Hp = 90;
	this->MonState.Mp = 85;
	this->MonState.ad = 16;
	this->MonState.ap = 16;
	this->MonState.adDef = 16;
	this->MonState.apDef = 16;
	this->MonState.EXP = 145;
}
void Ent::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Ent::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Ent::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Ent::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Ent::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Ent::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Ent::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Ent::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Ent::Skill_1() {
	this->SkillName_1 = "간지럼 태우기";
}
void Ent::Skill_2() {
	this->SkillName_2 = "손으로 지르기";
}
void Ent::Skill_3() {
	this->SkillName_3 = "까마귀떼 집중공격";
}
void Ent::Skill_4() {
	this->SkillName_4 = "늑대 부리기";
}

Behymes::Behymes() : cMonster() { }
Behymes::~Behymes() { }
void Behymes::SetMonState() {
	this->MonState.Hp = 110;
	this->MonState.Mp = 105;
	this->MonState.ad = 24;
	this->MonState.ap = 24;
	this->MonState.adDef = 24;
	this->MonState.apDef = 24;
	this->MonState.EXP = 150;
}
void Behymes::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Behymes::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Behymes::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Behymes::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Behymes::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Behymes::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Behymes::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Behymes::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Behymes::Skill_1() {
	this->SkillName_1 = "지면강타";
}
void Behymes::Skill_2() {
	this->SkillName_2 = "천둥소리";
}
void Behymes::Skill_3() {
	this->SkillName_3 = "지진의 파편";
}
void Behymes::Skill_4() {
	this->SkillName_4 = "분쇄";
}

Lich::Lich() : cMonster() { }
Lich::~Lich() { }
void Lich::SetMonState() {
	this->MonState.Hp = 130;
	this->MonState.Mp = 125;
	this->MonState.ad = 32;
	this->MonState.ap = 32;
	this->MonState.adDef = 32;
	this->MonState.apDef = 32;
	this->MonState.EXP = 155;
}
void Lich::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void Lich::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void Lich::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void Lich::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void Lich::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void Lich::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void Lich::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void Lich::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void Lich::Skill_1() {
	this->SkillName_1 = "황폐화";
}
void Lich::Skill_2() {
	this->SkillName_2 = "고통의 벽";
}
void Lich::Skill_3() {
	this->SkillName_3 = "부패";
}
void Lich::Skill_4() {
	this->SkillName_4 = "진흔곡";
}

RedDragon::RedDragon() : cMonster() { }
RedDragon::~RedDragon() { }
void RedDragon::SetMonState() {
	this->MonState.Hp = 200;
	this->MonState.Mp = 250;
	this->MonState.ad = 50;
	this->MonState.ap = 50;
	this->MonState.adDef = 50;
	this->MonState.apDef = 50;
	this->MonState.EXP = 160;
}
void RedDragon::SetBurn(int turn) {
	this->burnning.burn = true;
	this->burnning.turn += turn;
}
void RedDragon::SetBurnTurn() {
	if (burnning.turn > 0) this->burnning.turn--;
	if (burnning.turn == 0) this->burnning.burn = false;
}
void RedDragon::SetBleed(int turn) {
	this->Bleeding.bleeding = true;
	this->Bleeding.turn += turn;
}
void RedDragon::SetBleedTurn() {
	if (burnning.turn > 0) this->Bleeding.turn--;
	if (burnning.turn == 0) this->Bleeding.bleeding = false;
}
void RedDragon::SetSturn(int turn) {
	this->Sturned.sturn = true;
	this->Sturned.turn += turn;
}
void RedDragon::SetSturnTurn() {
	if (Sturned.turn > 0) this->Sturned.turn--;
	if (Sturned.turn == 0) this->Sturned.sturn = false;
}
void RedDragon::SetTunt(int turn) {
	this->Tuanted.taunt = true;
	this->Tuanted.turn += turn;
}
void RedDragon::SetTuntTurn() {
	if (Tuanted.turn > 0) this->Tuanted.turn--;
	if (Tuanted.turn == 0) this->Tuanted.taunt = false;
}
void RedDragon::Skill_1() {
	this->SkillName_1 = "돌진";
}
void RedDragon::Skill_2() {
	this->SkillName_2 = "바디 프레스";
}
void RedDragon::Skill_3() {
	this->SkillName_3 = "연속 브레스";
}
void RedDragon::Skill_4() {
	this->SkillName_4 = "차지 브레스";
}

Blank::Blank() : cMonster() { }
Blank::~Blank() { }
