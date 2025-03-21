#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
    forest = new Model("Forest");
    //forest->SetShader(L"Basic/Texture.hlsl");
    forest->Scale() *= 10.0f;
    forest->UpdateWorld();
    //forest->SetShader(L"PostEffect/Fog.hlsl");

    fogBuffer = new FogBuffer();

    

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->AlphaToCoverage(true);

    

    skybox = new Skybox(L"Textures/Landscape/SpaceSky.dds");

    //Audio::Get()->Add("bgm", "Sounds/naruto.mp3", true, true);
    Audio::Get()->Add("move", "Sounds/move.wav", false, false, true);
    Audio::Get()->Add("pain", "Sounds/pain.wav", false, false, true);
    Audio::Get()->Add("hit", "Sounds/hit.wav", false, false, true);

    //Audio::Get()->Play("bgm");

    ParticleManager::Get()->Add("hit", "TextData/Particles/Hit.fx", 30);
}

GameScene::~GameScene()
{
    delete forest;
    

    delete blendState[0];
    delete blendState[1];    

    delete skybox;

    delete fogBuffer;

    ParticleManager::Delete();
}


void GameScene::Update()
{
    naruto->Update();

    KunaiManager::Get()->Update();
    RobotManager::Get()->Update();

    ParticleManager::Get()->Update();
}

void GameScene::PreRender()
{
}

void GameScene::Render()
{
    skybox->Render();

    naruto->Render();

    blendState[1]->SetState();
    fogBuffer->SetPS(10);
    forest->Render();
    blendState[0]->SetState();

    KunaiManager::Get()->Render();
    RobotManager::Get()->Render();    

    ParticleManager::Get()->Render();
}

void GameScene::PostRender()
{
    RobotManager::Get()->PostRender();

    naruto->PostRender();
}

void GameScene::GUIRender()
{
    naruto->GUIRender();

    ImGui::SliderFloat("Start", &fogBuffer->Get().start, 0, 1.0f);
    ImGui::SliderFloat("Random", &fogBuffer->Get().random, 0, 2.0f);
    ImGui::ColorEdit4("Color", (float*)&fogBuffer->Get().color);
}

void GameScene::Start()
{
    naruto = new Naruto();

    CAM->SetTarget(naruto);
    CAM->TargetOptionLoad("Naruto");
    CAM->LookAtTarget();

    KunaiManager::Get();
    RobotManager::Get()->SetTarget(naruto);
}

void GameScene::End()
{
    delete naruto;

    KunaiManager::Delete();
    RobotManager::Delete();
}
