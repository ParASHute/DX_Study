#include "Framework.h"

Steve::Steve() : SphereCollider(0.3f)
{
    Pos() = { 5, 5, 5 };    
        
    ClientToScreen(hWnd, &clientCenterPos);
    ShowCursor(false);

    mineUI = new MineUI();
}

Steve::~Steve()
{    
    delete mineUI;
}

void Steve::Update()
{
    Control();
    Jump();

    UpdateWorld();

    mineUI->Update();
}

void Steve::Render()
{
    Collider::Render();
}

void Steve::PostRender()
{    
    mineUI->PostRender();
}

void Steve::GUIRender()
{
    mineUI->GUIRender();
}

void Steve::Control()
{
    if (KEY_PRESS('W'))
        Pos() += Forward() * moveSpeed * DELTA;
    if (KEY_PRESS('S'))
        Pos() += Back() * moveSpeed * DELTA;
    if (KEY_PRESS('D'))
        Pos() += Right() * moveSpeed * DELTA;
    if (KEY_PRESS('A'))
        Pos() += Left() * moveSpeed * DELTA;

    if (!isJump && KEY_DOWN(VK_SPACE))
    {
        velocity = jumpPower;
        isJump = true;
    }

    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);  
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    
    CAM->Rot().y += delta.x * rotSpeed * DELTA;
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;

    Rot().y = CAM->Rot().y;

    if (KEY_DOWN(VK_LBUTTON))
        mineUI->Mining();

    if (KEY_DOWN(VK_RBUTTON))
        mineUI->Build();      

    if (KEY_DOWN(VK_ESCAPE))
        ShowCursor(true);

    if (KEY_DOWN(VK_F3))
        ShowCursor(false);
}

void Steve::Jump()
{
    velocity -= GRAVITY * DELTA;

    Pos().y += velocity * DELTA;

    float height = BlockManager::Get()->GetHeight(Pos());

    if (height > Pos().y - Radius())
    {
        Pos().y = height + Radius();
        velocity = 0.0f;

        isJump = false;
    }
}
