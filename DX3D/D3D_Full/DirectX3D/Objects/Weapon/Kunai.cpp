#include "Framework.h"

Kunai::Kunai(Transform* transform)
    : transform(transform)
{
    transform->Scale() *= 100.0f;

    collider = new SphereCollider();    
    collider->SetParent(transform);
    
    collider->Scale() *= 0.05f;
    collider->Pos().x = 0.1f;
}

Kunai::~Kunai()
{
    delete collider;
}

void Kunai::Update()
{
    if (!transform->Active()) return;

    time += DELTA;

    if (time > LIFE_TIME)
        transform->SetActive(false);

    transform->Pos() += direction * speed * DELTA;

    collider->UpdateWorld();
}

void Kunai::Render()
{
    collider->Render();
}

void Kunai::Throw(Vector3 pos, Vector3 dir)
{
    transform->SetActive(true);

    transform->Pos() = pos;
    direction = dir;

    transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2;

    time = 0.0f;
}
