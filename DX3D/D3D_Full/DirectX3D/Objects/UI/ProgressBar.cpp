#include "Framework.h"

ProgressBar::ProgressBar(wstring frontImageFile, wstring backImageFile)
    : Quad(frontImageFile)
{
    material->SetShader(L"UI/ProgressBar.hlsl");

    backImage = Texture::Add(backImageFile);

    valueBuffer = new FloatValueBuffer();
    valueBuffer->Get()[0] = fillAmount;
}

ProgressBar::~ProgressBar()
{
    delete valueBuffer;
}

void ProgressBar::Render()
{
    valueBuffer->SetPS(10);
    backImage->PSSet(10);

    Quad::Render();
}

void ProgressBar::SetAmount(float value)
{
    valueBuffer->Get()[0] = value;
}
