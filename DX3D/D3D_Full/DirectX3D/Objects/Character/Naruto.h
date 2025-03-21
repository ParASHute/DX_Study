#pragma once

class Naruto : public ModelAnimator
{
private:
    enum State
    {
        IDLE,
        RUN_F, RUN_B, RUN_L, RUN_R,
        THROW
    };

public:
    Naruto();
    ~Naruto();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();

private:
    void Control();
    void Move();
    void Rotate();
    void Attack();
    void SetAnimation();

    void SetState(State state);

    void EndThrow();
    void Throw();

private:
    Transform* rightHand;
    Model* kunai;

    State curState = IDLE;

    float moveSpeed = 500.0f;
    float rotSpeed = 1.0f;
    float deceleration = 5.0f;

    Vector3 velocity;
    Vector3 targetPos;

    bool isTarget;

    POINT clientCenterPos = { WIN_WIDTH >> 1, WIN_HEIGHT >> 1 };

    Quad* crossHair;

    LightBuffer::Light* light;
};