#include "stdafx.h"
#include "01_PlayerAnimationTest.h"

void PlayerAnimationTest::Init()
{
	player = new Player({ 200,200,0 }, { 100,100,1 });
}

void PlayerAnimationTest::Destroy()
{
	SAFE_DELETE(player);
}

void PlayerAnimationTest::Update()
{
	player->Update();
}

void PlayerAnimationTest::Render()
{
	player->Render();
}

void PlayerAnimationTest::PostRender()
{
}

void PlayerAnimationTest::GUI()
{
	player->GUI();
}
