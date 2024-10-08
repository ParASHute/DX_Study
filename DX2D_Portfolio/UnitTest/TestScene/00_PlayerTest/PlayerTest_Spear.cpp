#include "stdafx.h"
#include "PlayerTest_Spear.h"

void SpearPlayerTest::Init()
{
	player = new Player({ 100,100,0 }, { 100,100,1 });
}

void SpearPlayerTest::Destroy()
{
	SAFE_DELETE(player);
}

void SpearPlayerTest::Update()
{
	player->Update();
}

void SpearPlayerTest::Render()
{
	player->Render();
}

void SpearPlayerTest::PostRender()
{
}

void SpearPlayerTest::GUI()
{
	ImGui::Begin("player"); 
	{
		player->GUI();
	}
	ImGui::End();
}
