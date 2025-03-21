#pragma once

class ActionScene : public Scene
{
public:
    ActionScene();
    ~ActionScene();
        
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Human* human;
};