#pragma once

class Panel : public Quad
{
public:
    Panel(wstring bgTextureFile, wstring cancelBtnTextureFile);
    ~Panel();

    void Update();
    void Render();

    void Show(Vector2 pos);

    void SetIsDrag(bool value) { isDrag = value; }

    RectCollider* GetCollider() { return collider; }
private:
    void Drag();
    void OnClickCancel();

private:
    Button* cancelBtn;
    RectCollider* collider;

    Vector2 offset;    
    bool isDrag = false;
};