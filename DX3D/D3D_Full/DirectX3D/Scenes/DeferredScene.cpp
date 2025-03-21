#include "Framework.h"
#include "DeferredScene.h"

DeferredScene::DeferredScene()
{
    gBuffer = new GBuffer();

    forest = new Model("Forest");
    human = new Human();   

    material = new Material(L"Light/Deferred.hlsl");
    UINT vertices[4] = { 0, 1, 2, 3 };
    vertexBuffer = new VertexBuffer(vertices, sizeof(UINT), 4);
}

DeferredScene::~DeferredScene()
{
    delete gBuffer;

    delete forest;
    delete human;

    delete material;
    delete vertexBuffer;
}

void DeferredScene::Update()
{
    human->Update();
}

void DeferredScene::PreRender()
{
    gBuffer->SetMultiRenderTarget();

    forest->SetShader(L"Light/GBuffer.hlsl");
    human->SetShader(L"Light/AnimGBuffer.hlsl");
    human->GetCrowbar()->SetShader(L"Light/GBuffer.hlsl");

    forest->Render();
    human->Render();
}

void DeferredScene::Render()
{
    vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    gBuffer->SetSRVs();
    material->Set();    

    DC->Draw(4, 0);
}

void DeferredScene::PostRender()
{
    gBuffer->PostRender();
}

void DeferredScene::GUIRender()
{
}
