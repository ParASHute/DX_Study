#include "Framework.h"

Particle::Particle()
{
    material = new Material();

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->Alpha(true);

    depthState[0] = new DepthStencilState();
    depthState[1] = new DepthStencilState();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

Particle::~Particle()
{
    delete material;
    delete vertexBuffer;

    delete blendState[0];
    delete blendState[1];

    delete depthState[0];
    delete depthState[1];
}

void Particle::Render()
{
    if (!isActive) return;

    blendState[1]->SetState();
    depthState[1]->SetState();

    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

    material->Set();
    geometryShader->Set();

    DC->Draw(particleCount, 0);

    DC->GSSetShader(nullptr, nullptr, 0);

    blendState[0]->SetState();
    depthState[0]->SetState();
}

void Particle::Play(Vector3 position)
{
    isActive = true;
    this->position = position;
}

void Particle::Stop()
{
    isActive = false;
}
