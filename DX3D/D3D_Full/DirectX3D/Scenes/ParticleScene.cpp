#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
    //particle = new Sprite(L"Textures/Effect/fire_8x2.png", 5, 20, 8, 2, true);
    //particle = new Sprite(L"Textures/Effect/explosion.png", 30, 30, 5, 3);
    //particle = new Spark(L"Textures/Effect/star.png", true);
    //particle = new Rain();
    //particle = new Snow();
    particle = new ParticleSystem("TextData/Particles/Hit.fx");
    //particle->Play(Vector3());

    collider = new SphereCollider(50);
}

ParticleScene::~ParticleScene()
{
    delete particle;
    delete collider;
}

void ParticleScene::Update()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        Ray ray = CAM->ScreenPointToRay(mousePos);
        Contact contact;

        if (collider->IsRayCollision(ray, &contact))
        {
            particle->Play(contact.hitPoint);
        }
    }

    particle->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
    particle->Render();
    collider->Render();
}

void ParticleScene::PostRender()
{
}

void ParticleScene::GUIRender()
{
    //particle->GUIRender();
}
