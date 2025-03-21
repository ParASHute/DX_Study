#include "Framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
    models = new ModelAnimatorInstancing("Naruto");
    models->ReadClip("Idle");
    models->ReadClip("Punching");

    for (float z = 0; z < SIZE; z++)
    {
        for (float x = 0; x < SIZE; x++)
        {
            Transform* transform = models->Add();
            transform->Pos() = { x, 0.0f, z };
            transform->Scale() *= 0.01f;
        }
    }
}

InstancingScene::~InstancingScene()
{
    delete models;
}

void InstancingScene::Update()
{
    models->Update();
}

void InstancingScene::PreRender()
{
}

void InstancingScene::Render()
{
    models->Render();
}

void InstancingScene::PostRender()
{
}

void InstancingScene::GUIRender()
{
    ImGui::SliderInt("ID", &instanceID, 0, 100);
    ImGui::SliderInt("Clip", &clip, 0, 1);

    if (ImGui::Button("Play"))
        models->PlayClip(instanceID, clip);

    models->GUIRender();
}
