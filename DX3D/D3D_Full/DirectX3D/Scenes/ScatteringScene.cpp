#include "Framework.h"
#include "ScatteringScene.h"

ScatteringScene::ScatteringScene()
{
    scattering = new Scattering();    
}

ScatteringScene::~ScatteringScene()
{
    delete scattering;
}

void ScatteringScene::Update()
{
}

void ScatteringScene::PreRender()
{    
    scattering->PreRender();
}

void ScatteringScene::Render()
{
    scattering->Render();
}

void ScatteringScene::PostRender()
{
    scattering->PostRender();
}

void ScatteringScene::GUIRender()
{
    scattering->GUIRender();
}
