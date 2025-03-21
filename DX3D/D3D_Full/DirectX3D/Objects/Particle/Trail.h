#pragma once

class Trail : public GameObject
{
public:
    Trail(wstring imageFile, Transform* start, Transform* end, UINT width, float speed);
    ~Trail();

    void Update();
    void Render();    

private:
    void CreateMesh();

private:    
    Mesh<VertexUV>* mesh;

    Transform* start, *end;

    UINT width;
    float speed;

    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];
};