#pragma once

class BillboardScene : public Scene
{
private:
    const UINT COUNT = 1000;

public:
    BillboardScene();
    ~BillboardScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    //vector<Quad*> trees;
    Material* material;
    VertexBuffer* vertexBuffer;

    GeometryShader* geometryShader;

    Terrain* terrain;

    BlendState* blendState[2];
    DepthStencilState* depthState[2];

    vector<VertexUV> vertices;
};