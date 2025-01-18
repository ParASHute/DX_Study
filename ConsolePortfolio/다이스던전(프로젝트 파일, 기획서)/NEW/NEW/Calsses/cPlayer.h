#pragma once
#include "../Global/Define/GlobalDefine.h"
class cPlayer{
private:

protected:
	struct State {
		string Tag;
		int Hp;
		int Mp;
		int ad;
		int ap;
		int adDef;
		int apDef;
		int speed;
	};
	struct MaxState {
		int Hp;
		int Mp;
		int ad;
		int ap;
		int adDef;
		int apDef;
		int MaxEXP;
	};
	struct Deffence {
		int adDef = 0;
		int apDef = 0;
	};
	MaxState maxState;
	State pState;
	Deffence Def;
	int Level = 1;
	int EXP = 0;
	string Name;
	string SkillName_1;
	string SkillName_2;
	string SkillName_3;
	string SkillName_4;


public:
	// 생성자 소멸자
	cPlayer() { }
	cPlayer(cPlayer& player);
	~cPlayer() { }

	// 세터
	virtual void SetName() { }
	virtual void SetMaxState() { }
	virtual void SetState() { }
	virtual void SetHp(int dam) { }
	virtual void SetLevel() { }
	virtual void SetExp(int Exp) { }
	virtual void SetAdDeffence(int addeff) { }
	virtual void SetApDeffence(int apdeff) { }
	virtual void GoHotel(int Hp, int Mp) { }
	virtual void UseSkill() { }


	// 게터
	virtual State	GetState() const { return this->pState; }
	virtual string	GetName() const { return this->Name; }
	virtual MaxState GetMaxState() const { return this->maxState; }
	virtual Deffence GetDeffence() const { return this->Def; }
	virtual int GetLevel() const { return this->Level; }
	virtual int GetEXP() const { return this->EXP; }
	virtual string	GetSkill_1Name() const { return this->SkillName_1; }
	virtual string	GetSkill_2Name() const { return this->SkillName_2; }
	virtual string	GetSkill_3Name() const { return this->SkillName_3; }
	virtual string	GetSkill_4Name() const { return this->SkillName_4; }

	// 버추얼(가상함수)
	virtual void Skill_1() { }
	virtual void Skill_2() { }
	virtual void Skill_3() { }
	virtual void Skill_4() { }
};

// 탱커
class HollyKnight : public cPlayer {
private:

protected:

public:
	// 생성자 소멸자
	HollyKnight();
	~HollyKnight();
	
	// 세터
	void SetName() override { this->Name = "성기사"; }
	void SetState() override;
	void SetMaxState() override;
	void SetHp(int dam) override { this->pState.Hp -= dam; }

	void SetLevel() override;
	void SetExp(int Exp) override;
	void SetAdDeffence(int addeff) override;
	void SetApDeffence(int apdeff) override;
	void GoHotel(int Hp, int Mp) override;
	void UseSkill() override;

	// 게터
	string GetName() const override { return this->Name; }
	State GetState() const override { return this->pState; }
	MaxState GetMaxState() const override { return this->maxState; }
	Deffence GetDeffence() const override { return this->Def; }
	int GetLevel() const override { return this->Level; }
	int GetEXP() const override { return this->EXP; }

	string GetSkill_1Name() const override { return this->SkillName_1; }
	string GetSkill_2Name() const override { return this->SkillName_2; }
	string GetSkill_3Name() const override { return this->SkillName_3; }
	string GetSkill_4Name() const override { return this->SkillName_4; }

	// 버추얼(가상함수)
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};

// 근딜
class Worrier : public cPlayer {
private:

protected:

public:
	// 생성자 소멸자
	Worrier();
	~Worrier();

	// 세터
	void SetName() override { this->Name = "검사"; }
	void SetState() override;
	void SetMaxState() override;
	void SetHp(int dam) override { this->pState.Hp -= dam; }
	void SetLevel() override;
	void SetExp(int Exp) override;
	void SetAdDeffence(int addeff) override;
	void SetApDeffence(int addeff) override;
	void GoHotel(int Hp, int Mp) override;
	void UseSkill() override;

	// 게터
	string GetName() const override { return this->Name; }
	State GetState() const override { return this->pState; }
	MaxState GetMaxState() const override { return this->maxState; }
	Deffence GetDeffence() const override { return this->Def; }
	int GetLevel() const override { return this->Level; }
	int GetEXP() const override { return this->EXP; }

	string GetSkill_1Name() const override { return this->SkillName_1; }
	string GetSkill_2Name() const override { return this->SkillName_2; }
	string GetSkill_3Name() const override { return this->SkillName_3; }
	string GetSkill_4Name() const override { return this->SkillName_4; }

	// 버추얼(가상함수)
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};

// 메이지
class Maige : public cPlayer {
private:

protected:

public:
	// 생성자 소멸자
	Maige();
	~Maige();

	// 세터
	void SetName() override { this->Name = "마법사"; }
	void SetState() override;
	void SetMaxState() override;
	void SetHp(int dam) override { this->pState.Hp -= dam; }
	void SetLevel() override;
	void SetExp(int Exp) override;
	void SetAdDeffence(int addeff) override;
	void SetApDeffence(int apdeff) override;
	void GoHotel(int Hp, int Mp) override;
	void UseSkill() override;

	// 게터
	string GetName() const override { return this->Name; }
	State GetState() const override { return this->pState; }
	MaxState GetMaxState() const override { return this->maxState; }
	Deffence GetDeffence() const override { return this->Def; }
	int GetLevel() const override { return this->Level; }
	int GetEXP() const override { return this->EXP; }

	string GetSkill_1Name() const override { return this->SkillName_1; }
	string GetSkill_2Name() const override { return this->SkillName_2; }
	string GetSkill_3Name() const override { return this->SkillName_3; }
	string GetSkill_4Name() const override { return this->SkillName_4; }

	// 버추얼(가상함수)
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};

// 힐러
class Cleric : public cPlayer {
private:

protected:

public:
	// 생성자 소멸자
	Cleric();
	~Cleric();
	
	// 세터
	void SetName() override { this->Name = "성직자"; }
	void SetState() override;
	void SetMaxState() override;
	void SetHp(int dam) override { this->pState.Hp -= dam; }
	void SetLevel() override;
	void SetExp(int Exp) override;
	void SetAdDeffence(int addeff) override;
	void SetApDeffence(int apdeff) override;
	void GoHotel(int Hp, int Mp) override;
	void UseSkill() override;

	// 게터
	string GetName() const override { return this->Name; }
	State GetState() const override { return this->pState; }
	MaxState GetMaxState() const override { return this->maxState; }
	Deffence GetDeffence() const override { return this->Def; }
	int GetLevel() const override { return this->Level; }
	int GetEXP() const override { return this->EXP; }

	string GetSkill_1Name() const override { return this->SkillName_1; }
	string GetSkill_2Name() const override { return this->SkillName_2; }
	string GetSkill_3Name() const override { return this->SkillName_3; }
	string GetSkill_4Name() const override { return this->SkillName_4; }

	// 버추얼(가상함수)
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};