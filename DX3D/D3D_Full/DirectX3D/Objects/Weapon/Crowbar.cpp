#include "Framework.h"

Crowbar::Crowbar() : Model("crowbar")
{
    SetTag("Crowbar");

    collider = new BoxCollider();
    collider->SetTag("CrowbarCollider");
    collider->SetParent(this);
    collider->Load();
}

Crowbar::~Crowbar()
{
    delete collider;
}

void Crowbar::Update()
{
    UpdateWorld();
    collider->UpdateWorld();
}

void Crowbar::Render()
{
    Model::Render();
    collider->Render();
}

void Crowbar::GUIRender()
{
    Model::GUIRender();
    collider->GUIRender();
}
