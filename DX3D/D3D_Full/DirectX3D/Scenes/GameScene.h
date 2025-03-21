#pragma once

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    virtual void Start() override;
    virtual void End() override;

private:
    Model* forest;
    Naruto* naruto;

    BlendState* blendState[2];

    Skybox* skybox;

    FogBuffer* fogBuffer;
};