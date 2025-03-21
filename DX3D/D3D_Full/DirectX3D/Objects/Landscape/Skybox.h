#pragma once

class Skybox : public Sphere
{
public:
    Skybox(wstring textureFile);
    ~Skybox();

    void Render();

private:
    Texture* cubeMap;

    RasterizerState* rasterizerState[2];
    DepthStencilState* depthStencilState[2];
};