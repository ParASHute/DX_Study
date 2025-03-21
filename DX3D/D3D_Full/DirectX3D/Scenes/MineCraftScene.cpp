#include "Framework.h"
#include "MineCraftScene.h"

MineCraftScene::MineCraftScene()
{
    BlockManager::Get()->CraeteBlocks(10, 10);

    steve = new Steve();

    CAM->SetTarget(steve);
    CAM->TargetOptionLoad("Mine");
}

MineCraftScene::~MineCraftScene()
{
    BlockManager::Delete();

    delete steve;
}

void MineCraftScene::Update()
{
    BlockManager::Get()->Update();
    steve->Update();

    BlockManager::Get()->Push(steve);
}

void MineCraftScene::PreRender()
{
}

void MineCraftScene::Render()
{
    BlockManager::Get()->Render();
    steve->Render();
}

void MineCraftScene::PostRender()
{
    steve->PostRender();
}

void MineCraftScene::GUIRender()
{
    steve->GUIRender();
}
