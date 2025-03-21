#include "Framework.h"

Naruto::Naruto() : ModelAnimator("Naruto")
{    
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    rightHand = new Transform();
    kunai = new Model("Kunai");
    kunai->SetParent(rightHand);
    kunai->SetTag("Kunai");
    kunai->Load();

    crossHair = new Quad(L"Textures/UI/cursor.png");
    crossHair->Pos() = { CENTER_X, CENTER_Y, 0 };
    crossHair->UpdateWorld();

    ReadClip("Idle");
    ReadClip("Run");
    ReadClip("RunBack");
    ReadClip("RunLeft");
    ReadClip("RunRight");
    ReadClip("Throw");

    GetClip(THROW)->SetEvent(bind(&Naruto::Throw, this), 0.7f);
    GetClip(THROW)->SetEvent(bind(&Naruto::EndThrow, this), 0.9f);

    light = Environment::Get()->GetLight(0);
    light->range = 1000.0f;
    light->color = { 1, 0.5f, 0.5f, 1};
}

Naruto::~Naruto()
{
    delete rightHand;
    delete kunai;
}

void Naruto::Update()
{
    light->pos = Pos() + Vector3(0, 100, 0);
    light->direction = CAM->Forward();

    Control();
    SetAnimation();

    rightHand->SetWorld(GetTransformByNode(38));

    ModelAnimator::Update();

    kunai->UpdateWorld();
}

void Naruto::Render()
{
    ModelAnimator::Render();

    kunai->Render();
}

void Naruto::PostRender()
{
    crossHair->Render();
}

void Naruto::GUIRender()
{
    Model::GUIRender();
    kunai->GUIRender();
}

void Naruto::Control()
{
    Rotate();
    Move();
    Attack();    
}

void Naruto::Move()
{
    if (curState == THROW) return;

    bool isMoveZ = false;
    bool isMoveX = false;

    if (KEY_PRESS('W'))
    {
        velocity.z += DELTA;
        isMoveZ = true;
    }
    if (KEY_PRESS('S'))
    {
        velocity.z -= DELTA;
        isMoveZ = true;
    }
    if (KEY_PRESS('A'))
    {
        velocity.x -= DELTA;
        isMoveX = true;
    }
    if (KEY_PRESS('D'))
    {
        velocity.x += DELTA;
        isMoveX = true;
    }

    if (velocity.Length() > 1.0f)
        velocity.Normalize();

    if (!isMoveX)
        velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

    if (!isMoveZ)
        velocity.z = Lerp(velocity.z, 0, deceleration * DELTA);

    Matrix rotY = XMMatrixRotationY(Rot().y);
    Vector3 direction = XMVector3TransformCoord(velocity, rotY);

    Pos() -= direction * moveSpeed * DELTA;
}

void Naruto::Rotate()
{
    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    Rot().y += delta.x * rotSpeed * DELTA;
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
}

void Naruto::Attack()
{
    if (curState == THROW) return;

    if (KEY_DOWN(VK_LBUTTON))
    {
        SetState(THROW);   

        Ray ray = CAM->ScreenPointToRay(mousePos);
        isTarget = RobotManager::Get()->IsCollision(ray, targetPos);
    }
}

void Naruto::SetAnimation()
{
    if (curState == THROW) return;

    if (velocity.z > 0.1f)
        SetState(RUN_F);
    else if (velocity.z < -0.1f)
        SetState(RUN_B);
    else if (velocity.x > 0.1f)
        SetState(RUN_R);
    else if (velocity.x < -0.1f)
        SetState(RUN_L);
    else
        SetState(IDLE);
}

void Naruto::SetState(State state)
{
    if (curState == state) return;

    curState = state;
    PlayClip(state);
}

void Naruto::EndThrow()
{
    SetState(IDLE);    
}

void Naruto::Throw()
{
    Vector3 dir = Back();

    if (isTarget)
    {
        dir = targetPos - kunai->GlobalPos();
    }
     
    KunaiManager::Get()->Throw(kunai->GlobalPos(), dir.GetNormalized());
}
