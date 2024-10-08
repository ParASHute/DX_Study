#include "Framework.h"
#include "Monster.h"

Monster::Monster(Vector3 position, Vector3 size, MonsterType type, float rotation)
	:position(position), size(size), type(type)
{
	body = new AnimationRect(position, size);
}

Monster::Monster(Vector3 position, Vector3 size, float rotation)
{
	body = new AnimationRect(position, size);
}

Monster::~Monster()
{
}

void Monster::Update()
{
}

void Monster::Render()
{
}

void Monster::Move()
{
}

void Monster::Attack()
{
}

void Monster::GUI()
{
}

string Monster::MakeLable(string lable)
{
	return string();
}

void Monster::SetMonsterType()
{
}

void Monster::MakeAni()
{
}
