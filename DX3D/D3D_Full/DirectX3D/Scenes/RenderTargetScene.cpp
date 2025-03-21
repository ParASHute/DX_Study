#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
    forest = new Model("Forest");
    human = new Human();

    renderTarget = new RenderTarget();
    depthStencil = new DepthStencil();

    quad = new Quad(Vector2(500, 500));
    quad->Pos() = { CENTER_X, CENTER_Y };
    quad->GetMaterial()->SetShader(L"PostEffect/Bloom.hlsl");
    quad->GetMaterial()->SetDiffuseMap(Texture::Add(L"Render", renderTarget->GetSRV()));
    quad->UpdateWorld();

    valueBuffer = new FloatValueBuffer();
    valueBuffer->Get()[0] = 0.9f;
    valueBuffer->Get()[1] = 4.0f;
}

RenderTargetScene::~RenderTargetScene()
{
    delete forest;
    delete human;

    delete renderTarget;
    delete depthStencil;

    delete quad;
    delete valueBuffer;
}

void RenderTargetScene::Update()
{
    human->Update();
}

void RenderTargetScene::PreRender()
{
    renderTarget->Set(depthStencil);

    forest->Render();
    human->Render();
}

void RenderTargetScene::Render()
{    
}

void RenderTargetScene::PostRender()
{
    valueBuffer->SetPS(10);
    quad->Render();
}

void RenderTargetScene::GUIRender()
{
    ImGui::SliderFloat("Threshold", &valueBuffer->Get()[0], 0, 1.0f);
    ImGui::SliderFloat("Value", &valueBuffer->Get()[1], 0, 10);
}
