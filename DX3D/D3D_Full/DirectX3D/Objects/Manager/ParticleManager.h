#pragma once

class ParticleManager : public Singleton<ParticleManager>
{
private:
    friend class Singleton;

    ParticleManager();
    ~ParticleManager();

public:
    void Update();
    void Render();

    void Play(string key, Vector3 pos, Vector3 rot = Vector3());
    
    void Add(string key, string file, UINT poolSize);

private:
    typedef vector<ParticleSystem*> Particles;
    map<string, Particles> totalParticle;
};