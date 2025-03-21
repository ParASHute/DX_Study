#pragma once

class ModelRenderScene : public Scene
{
public:
    ModelRenderScene();
    ~ModelRenderScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    void SaveMaterial();

private:
    int selectMeshNum = 0;

    Model* model;
};