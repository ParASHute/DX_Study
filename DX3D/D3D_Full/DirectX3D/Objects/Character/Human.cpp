#include "Framework.h"

Human::Human() : ModelAnimator("Human")
{
    crowbar = new Crowbar();
    crowbar->Load();

    ReadClip("Idle", 1);
    ReadClip("Run", 1);
    ReadClip("Jump", 1);

    rightHand = new Transform();
    crowbar->SetParent(rightHand);

    startEdge = new Transform();
    endEdge = new Transform();
    startEdge->Pos() = { 0, 100, 0 };
    endEdge->Pos() = { 0, 10, 0 };

    trail = new Trail(L"Textures/Effect/Trail.png", startEdge, endEdge, 10, 10.0f);

    PlayClip(1);
}

Human::~Human()
{
    delete crowbar;
    delete rightHand;

    delete trail;

    delete startEdge;
    delete endEdge;
}

void Human::Update()
{
    rightHand->SetWorld(GetTransformByNode(51));

    startEdge->Pos() = crowbar->GlobalPos() + crowbar->Up() * 200.0f;    
    endEdge->Pos() = crowbar->GlobalPos() - crowbar->Up() * 200.0f;

    startEdge->UpdateWorld();
    endEdge->UpdateWorld();

    crowbar->Update();

    ModelAnimator::Update();

    trail->Update();
}

void Human::Render()
{
    crowbar->Render();
    ModelAnimator::Render();

    trail->Render();
}

void Human::GUIRender()
{
    crowbar->GUIRender();
}
