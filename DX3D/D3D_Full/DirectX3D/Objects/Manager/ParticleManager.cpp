#include "Framework.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
    for (auto particles : totalParticle)
    {
        for (ParticleSystem* particle : particles.second)
        {
            delete particle;
        }
    }
}

void ParticleManager::Update()
{
    for (auto particles : totalParticle)
    {
        for (ParticleSystem* particle : particles.second)
        {
            particle->Update();
        }
    }
}

void ParticleManager::Render()
{
    for (auto particles : totalParticle)
    {
        for (ParticleSystem* particle : particles.second)
        {
            particle->Render();
        }
    }
}

void ParticleManager::Play(string key, Vector3 pos, Vector3 rot)
{
    if (totalParticle.count(key) == 0) return;

    for (ParticleSystem* particle : totalParticle[key])
    {
        if (!particle->IsActive())
        {
            particle->Play(pos, rot);
            return;
        }
    }
}

void ParticleManager::Add(string key, string file, UINT poolSize)
{
    if (totalParticle.count(key) > 0) return;

    Particles particles(poolSize);

    for (ParticleSystem*& particle : particles)
    {
        particle = new ParticleSystem(file);
    }

    totalParticle[key] = particles;
}
