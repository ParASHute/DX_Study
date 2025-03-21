#include "Framework.h"

ParticleSystem::ParticleSystem(string file)
{
    LoadData(file);

    instanceBuffer = new VertexBuffer(instances.data(),
        sizeof(InstanceData), data.count);

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->Alpha(true);

    depthState[0] = new DepthStencilState();
    depthState[1] = new DepthStencilState();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    quad->SetActive(false);
}

ParticleSystem::~ParticleSystem()
{
    delete quad;
    delete instanceBuffer;

    delete blendState[0];
    delete blendState[1];

    delete depthState[0];
    delete depthState[1];
}

void ParticleSystem::Update()
{
    if (!quad->Active()) return;

    lifeTime += DELTA;

    UpdatePhysical();
    UpdateColor();
    quad->UpdateWorld();

    if (lifeTime > data.duration)
    {
        if (data.isLoop)
            Init();
        else
            Stop();
    }        
}

void ParticleSystem::Render()
{
    if (!quad->Active()) return;

    instanceBuffer->Set(1);

    quad->SetRender();

    blendState[1]->SetState();
    depthState[1]->SetState();

    DC->DrawIndexedInstanced(6, drawCount, 0, 0, 0);

    blendState[0]->SetState();
    depthState[0]->SetState();
}

void ParticleSystem::Play(Vector3 pos, Vector3 rot)
{
    quad->SetActive(true);

    quad->Pos() = pos;
    quad->Rot() = rot;
    
    Init();
}

void ParticleSystem::Stop()
{
    quad->SetActive(false);
}

void ParticleSystem::UpdatePhysical()
{
    drawCount = 0;

    FOR(data.count)
    {
        if (particleInfos[i].startTime > lifeTime) continue;

        particleInfos[i].velocity += particleInfos[i].accelation * DELTA;
        particleInfos[i].transform.Pos() += particleInfos[i].velocity * particleInfos[i].speed * DELTA;
        particleInfos[i].transform.Rot().z += particleInfos[i].angularVelocity * DELTA;
        if (data.isBillboard)
        {
            particleInfos[i].transform.Rot().x = CAM->Rot().x;
            particleInfos[i].transform.Rot().y = CAM->Rot().y;
        }

        float t = (lifeTime - particleInfos[i].startTime)
            / (data.duration - particleInfos[i].startTime);

        particleInfos[i].transform.Scale() =
            Lerp(particleInfos[i].startScale, particleInfos[i].endScale, t);

        particleInfos[i].transform.UpdateWorld();
        instances[drawCount++].transform =
            XMMatrixTranspose(particleInfos[i].transform.GetWorld());
    }

    instanceBuffer->Update(instances.data(), drawCount);
}

void ParticleSystem::UpdateColor()
{
    float t = lifeTime / data.duration;

    Float4 color;
    color.x = Lerp(data.startColor.x, data.endColor.x, t);
    color.y = Lerp(data.startColor.y, data.endColor.y, t);
    color.z = Lerp(data.startColor.z, data.endColor.z, t);
    color.w = Lerp(data.startColor.w, data.endColor.w, t);

    quad->GetMaterial()->GetData().diffuse = color;
}

void ParticleSystem::Init()
{
    if (data.isAdditive)
        blendState[1]->Additive();
    else
        blendState[1]->Alpha(true);

    lifeTime = 0.0f;
    drawCount = 0;
    data.count = particleCount;

    instances.resize(data.count);
    particleInfos.resize(data.count);

    for (ParticleInfo& info : particleInfos)
    {
        info.transform.Pos() = {};

        info.velocity = Random(data.minVelocity, data.maxVelocity);
        info.accelation = Random(data.minAccelation, data.maxAccelation);
        info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        info.speed = Random(data.minSpeed, data.maxSpeed);
        info.startTime = Random(data.minStartTime, data.maxStartTime);
        info.startScale = Random(data.minStartScale, data.maxStartScale);
        info.endScale = Random(data.minEndScale, data.maxEndScale);
        info.velocity.Normalize();
    }
}


void ParticleSystem::LoadData(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    wstring textureFile = reader->WString();
    quad = new Quad(Vector2(1, 1));
    quad->GetMaterial()->SetDiffuseMap(textureFile);
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl");

    ParticleData* particleData = new ParticleData();
    reader->Byte((void**)&particleData, sizeof(ParticleData));

    data = *particleData;

    instances.resize(data.count);
    particleInfos.resize(data.count);    

    delete reader;
}
