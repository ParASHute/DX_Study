#pragma once

class TutorialScene : public Scene
{
public:
    TutorialScene();
    ~TutorialScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    VertexShader* vertexShader;
    PixelShader* pixelShader;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    MatrixBuffer* worldBuffer;

    vector<VertexColor> vertices;
    vector<UINT> indices;
};