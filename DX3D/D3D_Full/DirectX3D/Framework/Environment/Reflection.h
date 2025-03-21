#pragma once

class Reflection
{
public:
    Reflection(Transform* target);
    ~Reflection();

    void Update();

    void SetReflection();
    void SetRender();
    void PostRender();

private:
    Transform* target;

    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    Camera* camera;

    class Quad* quad;
};