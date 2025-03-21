#pragma once

class DeferredScene : public Scene
{
public:
    DeferredScene();
    ~DeferredScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    GBuffer* gBuffer;

    Model* forest;
    Human* human;

    Material* material;
    VertexBuffer* vertexBuffer;
};