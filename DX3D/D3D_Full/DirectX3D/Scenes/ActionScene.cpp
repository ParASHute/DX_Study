#include "Framework.h"
#include "ActionScene.h"

ActionScene::ActionScene()
{
    human = new Human();
}

ActionScene::~ActionScene()
{
    delete human;
}

void ActionScene::Update()
{
    if (KEY_DOWN('1'))
        human->PlayClip(0);
    if (KEY_DOWN('2'))
        human->PlayClip(1, 0.1f);
    if (KEY_DOWN('3'))
        human->PlayClip(2);

    human->Update();
}

void ActionScene::PreRender()
{
}

void ActionScene::Render()
{
    human->Render();
}

void ActionScene::PostRender()
{
}

void ActionScene::GUIRender()
{
    human->GUIRender();
}
