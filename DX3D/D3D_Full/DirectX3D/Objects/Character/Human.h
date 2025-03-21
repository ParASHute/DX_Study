#pragma once

class Human : public ModelAnimator
{
public:
    Human();
    ~Human();

    void Update();
    void Render();
    void GUIRender();

    Crowbar* GetCrowbar() { return crowbar; }

private:
    Crowbar* crowbar;
    Transform* rightHand;

    Transform* startEdge;
    Transform* endEdge;

    Trail* trail;
};