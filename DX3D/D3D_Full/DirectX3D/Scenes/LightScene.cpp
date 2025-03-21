#include "Framework.h"
#include "LightScene.h"

LightScene::LightScene()
{
    sphere = new Sphere(10);  
    sphere->GetMaterial()->GetName() = "Fieldstone";
}

LightScene::~LightScene()
{
    delete sphere;
}

void LightScene::Update()
{
    if (KEY_PRESS(VK_F2))
        sphere->GetMaterial()->Load("TextData/Materials/Fieldstone.mat");

    sphere->UpdateWorld();
}

void LightScene::PreRender()
{
}

void LightScene::Render()
{
    sphere->Render();
}

void LightScene::PostRender()
{    
}

void LightScene::GUIRender()
{
    sphere->GUIRender();
}
