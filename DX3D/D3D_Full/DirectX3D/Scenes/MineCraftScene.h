#pragma once

class MineCraftScene : public Scene
{
public:
    MineCraftScene();
    ~MineCraftScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Steve* steve;
};