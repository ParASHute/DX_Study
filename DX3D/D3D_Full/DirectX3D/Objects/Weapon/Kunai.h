#pragma once

class Kunai
{
private:
    const float LIFE_TIME = 5.0f;

public:
    Kunai(Transform* transform);
    ~Kunai();

    void Update();
    void Render();    

    void Throw(Vector3 pos, Vector3 dir);

    SphereCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

private:
    Transform* transform;
    SphereCollider* collider;

    float speed = 1000.0f;
    float time = 0.0f;

    Vector3 direction;
};