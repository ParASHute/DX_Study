#include "Framework.h"

KunaiManager::KunaiManager()
{
    kunaiInstancing = new ModelInstancing("Kunai");

    kunaies.reserve(SIZE);
    FOR(SIZE)
    {
        Transform* transform = kunaiInstancing->Add();
        transform->SetActive(false);
        Kunai* kunai = new Kunai(transform);
        kunaies.push_back(kunai);
    }
}

KunaiManager::~KunaiManager()
{
    delete kunaiInstancing;

    for (Kunai* kunai : kunaies)
        delete kunai;
}

void KunaiManager::Update()
{
    kunaiInstancing->Update();

    for (Kunai* kunai : kunaies)
        kunai->Update();
}

void KunaiManager::Render()
{
    kunaiInstancing->Render();

    for (Kunai* kunai : kunaies)
        kunai->Render();
}

void KunaiManager::Throw(Vector3 pos, Vector3 dir)
{
    for (Kunai* kunai : kunaies)
    {
        if (!kunai->GetTransform()->Active())
        {
            kunai->Throw(pos, dir);
            return;
        }
    }
}

bool KunaiManager::IsCollision(Collider* collider)
{
    for (Kunai* kunai : kunaies)
    {
        if (kunai->GetCollider()->IsCollision(collider))
        {
            ParticleManager::Get()->Play("hit", kunai->GetTransform()->GlobalPos());
            kunai->GetTransform()->SetActive(false);
            return true;
        }
    }

    return false;
}
