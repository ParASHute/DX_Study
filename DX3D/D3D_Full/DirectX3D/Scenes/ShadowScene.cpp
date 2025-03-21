#include "Framework.h"
#include "ShadowScene.h"

ShadowScene::ShadowScene()
{
    forest = new Model("Forest");
    human = new Human();

    shadow = new Shadow();

    LightBuffer::Light* light = Environment::Get()->GetLight(0);
    light->type = 1;
    light->pos = { 0, 700, -500 };
    light->range = 2000.0f;
}

ShadowScene::~ShadowScene()
{
    delete forest;
    delete human;
}

void ShadowScene::Update()
{
    human->Update();
}

void ShadowScene::PreRender()
{
    shadow->SetRenderTarget();

    //forest->SetShader(L"Light/DepthMap.hlsl");
    human->SetShader(L"Light/DepthMap.hlsl");
    human->GetCrowbar()->SetShader(L"Light/DepthMap.hlsl");

    //forest->Render();
    human->Render();

}

void ShadowScene::Render()
{
    shadow->SetRender();

    forest->SetShader(L"Light/Shadow.hlsl");
    human->SetShader(L"Light/Shadow.hlsl");
    human->GetCrowbar()->SetShader(L"Light/Shadow.hlsl");

    forest->Render();
    human->Render();
}

void ShadowScene::PostRender()
{
    shadow->PostRender();
}

void ShadowScene::GUIRender()
{
    shadow->GUIRender();
}
