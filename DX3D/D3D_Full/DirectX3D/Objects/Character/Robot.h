#pragma once

class Robot
{
private:
    enum State
    {
        STAND_UP,
        WALK, RUN,
        HIT, DYING
    };

public:
    Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~Robot();

    void Update();
    void Render();
    void PostRender();

    void Hit();

    void Spawn(Vector3 pos);

    CapsuleCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

    void SetTarget(Transform* target) { this->target = target; }

private:    
    void SetEvent(int clip, Event event, float timeRatio);
    void ExcuteEvent();

    void EndStandUp();
    void EndHit();    
    void EndDying();

    void SetState(State state);

    void Move();
    void UpdateHpBar();

private:
    Transform* transform;
    CapsuleCollider* collider;
    ModelAnimatorInstancing* instancing;    
    ModelAnimatorInstancing::Motion* motion;
    Transform* root;
    ProgressBar* hpBar;
    Transform* target;

    float speed = 50.0f;    
    float maxHp = 100.0f;
    float curHp = 100.0f;

    Vector3 velocity;
    Vector3 barPos;

    UINT index;
    State curState = STAND_UP;

    vector<map<float, Event>> totalEvent; 
    vector<map<float, Event>::iterator> eventIters;
};