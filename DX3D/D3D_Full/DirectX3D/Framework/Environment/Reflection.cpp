#include "Framework.h"

Reflection::Reflection(Transform* target)
    : target(target)
{
    renderTarget = new RenderTarget(2048, 2048);
    depthStencil = new DepthStencil(2048, 2048);

    camera = new Camera();

    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 };
    Texture* texture = Texture::Add(L"Reflection", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);
    quad->UpdateWorld();
}

Reflection::~Reflection()
{
    delete renderTarget;
    delete depthStencil;
    delete camera;
    delete quad;
}

void Reflection::Update()
{
    camera->Pos() = CAM->Pos();
    camera->Rot() = CAM->Rot();

    camera->Rot().x *= -1.0f;
    camera->Pos().y = target->Pos().y * 2.0f - camera->Pos().y;

    camera->UpdateWorld();
}

void Reflection::SetReflection()
{
    renderTarget->Set(depthStencil);
    camera->SetView();
}

void Reflection::SetRender()
{
    camera->GetViewBuffer()->SetVS(10);
    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV());    
}

void Reflection::PostRender()
{
    quad->Render();
}
