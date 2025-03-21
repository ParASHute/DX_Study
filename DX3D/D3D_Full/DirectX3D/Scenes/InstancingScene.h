#pragma once

class InstancingScene : public Scene
{
private:
    const UINT SIZE = 10;

public:
    InstancingScene();
    ~InstancingScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    ModelAnimatorInstancing* models;

    int instanceID = 0;
    int clip = 0;
};