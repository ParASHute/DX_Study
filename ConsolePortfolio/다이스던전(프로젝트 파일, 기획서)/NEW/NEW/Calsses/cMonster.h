#pragma once
#include "../Global/Define/GlobalDefine.h"
class cMonster{
private:

protected:
	struct MonsterState {
		string MonTag;
		int Hp;
		int Mp;
		int ad;
		int ap;
		int adDef;
		int apDef;
		int EXP;
	};
	struct Burn {
		bool burn = false;
		int turn = 0;
	};
	struct Bleed {
		bool bleeding = false;
		int turn = 0;
	};
	struct Sturn {
		bool sturn = false;
		int turn = 0;
	};
	struct Taunt {
		bool taunt = false;
		int turn = 0;
	};
	
	MonsterState MonState;
	Burn burnning;
	Bleed Bleeding;
	Sturn Sturned;
	Taunt Tuanted;

	string MonName;
	string SkillName_1;
	string SkillName_2;
	string SkillName_3;
	string SkillName_4;

	/*
		캡슐화를 하는 이유인 보안을 신경쓰기 위해서는
		아래 퍼블릭에 있는 모든 함수를(생성자, 소멸자 포함) 
		이 구역(protected)영역에 선언한다
		이때 함수들을 전부 가상함수화(virtual)하여
		자식 클라스에서 오버라이드 해서 사용한다.

		지금 처럼 선언시(1)
		class 자식 : protected 부모 { };의 형태로 상속이 가능하나

		퍼블릭에 선언 후 진행시(2)
		class 자식 : public 부모 { };의 형태로 상속해야 다형성을 활용할수 있다.

		프라이베이트에 선언 후 진행시(3)
		class 자식 : 부모 { };

		이때에 부모클라스 앞에 퍼블릭이 붙고 안붙고의 차이는 
		생성자의 위치에 있다.

		(1) : 생성자 소멸자가 protected영역에 존재
		(2) : 생성자 소멸자가 public영역에 존재
	*/
public:
	// 생성자 소멸자
	cMonster() { }
	cMonster(cMonster& monster);
	~cMonster() { }

	// 가상함수(버츄얼)
	// 버츄얼 세터 
	virtual void SetName() { }
	virtual void SetMonState() { }
	virtual void SetHp(int dam) { }
	virtual void PrintMonHp() { }

	virtual void SetBurn(int turn) { }
	virtual void SetBurnTurn() { }
	virtual void SetBleed(int turn) { }
	virtual void SetBleedTurn() { }
	virtual void SetSturn(int turn) { }
	virtual void SetSturnTurn() { }
	virtual void SetTunt(int turn) { }
	virtual void SetTuntTurn() { }

	virtual void Skill_1() { }
	virtual void Skill_2() { }
	virtual void Skill_3() { }
	virtual void Skill_4() { }
	

	// 버츄얼 게터
	virtual MonsterState GetMonState() const { return this->MonState; }
	virtual Burn GetBurn() const { return this->burnning; }
	virtual Bleed GetBleed() const { return this->Bleeding; }
	virtual Sturn GetSturn() const { return this->Sturned; }
	virtual Taunt GetTaunt() const { return this->Tuanted; }
	virtual string GetName() const { return this->MonName; }
	virtual void PrintfHP() {  }

	virtual string GetSkill_1Name() const { return this->SkillName_1; }
	virtual string GetSkill_2Name() const { return this->SkillName_2; }
	virtual string GetSkill_3Name() const { return this->SkillName_3; }
	virtual string GetSkill_4Name() const { return this->SkillName_4; }
};

// 빈칸에 생성할 몬스터 (혹시몰라 생성)
class Blank : public cMonster {
public:
	Blank();
	~Blank();

	void SetName() override { this->MonName = "Blank"; }
	void SetMonState() override { this->MonState.Hp = 0; }
};

// 잡몹
// 1스테이지 (초원)
class Slime : public cMonster { // 슬라임
public:
	// 생성자 소멸자
	Slime();
	~Slime();

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;

	// 세터 
	void SetName() override { this->MonName = "슬라임"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState()  const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }
};
class Gobllin : public cMonster { // 고블린
public:
	// 생성사 소멸자
	Gobllin();
	~Gobllin();

	// 세터 
	void SetName() override { this->MonName = "고블린"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Kobold : public cMonster { // 코볼트
public:
	Kobold();
	~Kobold();

	// 세터 
	void SetName() override { this->MonName = "고블린"; }
	void SetMonState() override ;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class LizardMan : public cMonster{ // 리자드맨
public:
	LizardMan();
	~LizardMan();

	// 세터 
	void SetName() override { this->MonName = "고블린"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};

// 2 스테이지 (사막)
class Scorpion : public cMonster { // 전갈
public:
	// 생성자 소멸자
	Scorpion();
	~Scorpion();

	// 세터 
	void SetName() override { this->MonName = "전갈"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Mummy : public cMonster { // 미라
public:
	// 생성자 소멸자
	Mummy();
	~Mummy();

	// 세터 
	void SetName() override { this->MonName = "미라"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Mimmic : public cMonster { // 미믹
public:
	// 생성자 소멸자
	Mimmic();
	~Mimmic();

	// 세터 
	void SetName() override { this->MonName = "미믹"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Sandman : public cMonster { // 샌드맨
public:
	// 생성자 소멸자
	Sandman();
	~Sandman();

	// 세터 
	void SetName() override { this->MonName = "샌드맨"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override  { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};

// 3스테이지 (무덤가)
class Skeleton : public cMonster { // 스캘래톤
public:
	// 생성자 소멸자
	Skeleton();
	~Skeleton();

	// 세터 
	void SetName() override { this->MonName = "스캘래톤"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Zombie : public cMonster { // 좀비
public:
	// 생성자 소멸자
	Zombie();
	~Zombie();

	// 세터 
	void SetName() override { this->MonName = "좀비"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Wraith : public cMonster { // 레이스
public:
	// 생성자 소멸자
	Wraith();
	~Wraith();

	// 세터 
	void SetName() override { this->MonName = "레이스"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Gagotle : public cMonster { // 가고일
public:
	// 생성자 소멸자
	Gagotle();
	~Gagotle();

	// 세터 
	void SetName() override { this->MonName = "가고일"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};

// 4스테이지 (설산)
class Yeti : public cMonster { // 예티
public:
	// 생성자 소멸자
	Yeti();
	~Yeti();

	// 세터 
	void SetName() override { this->MonName = "예티"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;
	
	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Gorlem : public cMonster { // 골램
public:
	// 생성자 소멸자
	Gorlem();
	~Gorlem();

	// 세터 
	void SetName() override { this->MonName = "골램"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class WereWolve : public cMonster { // 웨어울프
public:
	// 생성자 소멸자
	WereWolve();
	~WereWolve();

	// 세터 
	void SetName() override { this->MonName = "웨어울프"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Griffon : public cMonster { // 그리폰
public:
	// 생성자 소멸자
	Griffon();
	~Griffon();

	// 세터 
	void SetName() override { this->MonName = "그리폰"; }
	void SetMonState()override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};

// 중간 보스 
class Mandrake : public cMonster { // 맨드레이크
public:
	// 생성자 소멸자
	Mandrake();
	~Mandrake();

	// 세터 
	void SetName() override { this->MonName = "맨드레이크"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Sphinx : public cMonster { // 스핑크스
public:
	// 생성자 소멸자
	Sphinx();
	~Sphinx();

	// 세터 
	void SetName() override { this->MonName = "스핑크스"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Dullahan : public cMonster { // 듀라한
public:
	// 생성자 소멸자
	Dullahan();
	~Dullahan();

	// 세터 
	void SetName() override { this->MonName = "듀라한"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Wyvern : public cMonster { // 와이번
public:
	// 생성자 소멸자
	Wyvern();
	~Wyvern();

	// 세터 
	void SetName() override { this->MonName = "와이번"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};

// 보스몹
class Ent : public cMonster { // 앤트 (설명상으로는 위쳐-레셴 같은 몬스터인듯 오염된 세계수 컨샙으로 넣음)
public:
	// 생성자 소멸자
	Ent();
	~Ent();

	// 세터 
	void SetName() { this->MonName = "앤트"; }
	void SetMonState();
	void SetHp(int dam) { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Behymes : public cMonster { // 배히모스
public:
	// 생성자 소멸자
	Behymes();
	~Behymes();

	// 세터 
	void SetName() override { this->MonName = "배히모스"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class Lich : public cMonster { // 리치
public:
	// 생성자 소멸자
	Lich();
	~Lich();

	// 세터 
	void SetName() override { this->MonName = "리치"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};
class RedDragon : public  cMonster { // 드래곤
public:
	// 생성자 소멸자
	RedDragon();
	~RedDragon();

	// 세터 
	void SetName() override { this->MonName = "드래곤"; }
	void SetMonState() override;
	void SetHp(int dam) override { this->MonState.Hp -= dam; }

	void SetBurn(int turn) override;
	void SetBurnTurn() override;

	void SetBleed(int turn) override;
	void SetBleedTurn() override;

	void SetSturn(int turn) override;
	void SetSturnTurn() override;

	void SetTunt(int turn) override;
	void SetTuntTurn() override;

	// 게터
	MonsterState GetMonState() const override { return this->MonState; }
	Burn GetBurn() const override { return this->burnning; }
	Bleed GetBleed() const override { return this->Bleeding; }
	Sturn GetSturn() const override { return this->Sturned; }
	Taunt GetTaunt() const override { return this->Tuanted; }
	string GetName() const override { return this->MonName; }
	void PrintMonHp() override { cout << MonState.Hp << endl; }

	// 오버라이드
	void Skill_1() override;
	void Skill_2() override;
	void Skill_3() override;
	void Skill_4() override;
};