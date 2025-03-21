#include "Framework.h"

Panel::Panel(wstring bgTextureFile, wstring cancelBtnTextureFile)
    : Quad(bgTextureFile)
{
    cancelBtn = new Button(cancelBtnTextureFile);
    cancelBtn->SetParent(this);
    cancelBtn->Pos() = size * 0.5f - cancelBtn->GetSize() * 0.5f;
    cancelBtn->SetEvent(bind(&Panel::OnClickCancel, this));

    collider = new RectCollider(size);
    collider->SetParent(this);

    isActive = false;
}

Panel::~Panel()
{
    delete cancelBtn;
    delete collider;
}

void Panel::Update()
{
    if (!Active()) return;

    Drag();

    UpdateWorld();
    cancelBtn->Update();
    collider->UpdateWorld();
}

void Panel::Render()
{
    if (!Active()) return;

    Quad::Render();
    cancelBtn->Render();
    collider->Render();
}

void Panel::Show(Vector2 pos)
{
    Pos() = pos;
    isActive = true;
}

void Panel::Drag()
{
    if (cancelBtn->GetCollider()->IsPointCollision(mousePos)) return;
    if (collider->IsPointCollision(mousePos) == false) return;
    if (!isDrag) return;

    if (KEY_DOWN(VK_LBUTTON))
    {
        offset = mousePos - Pos();        
    }

    if (KEY_PRESS(VK_LBUTTON))
    {
        Pos() = mousePos - offset;
    }

    if (KEY_UP(VK_LBUTTON))
    {
        isDrag = false;
    }
}

void Panel::OnClickCancel()
{
    isActive = false;

    UIManager::Get()->Hide(tag);
}
