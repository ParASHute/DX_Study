#include "Framework.h"

Scattering::Scattering()
{
    targetBuffer = new TargetBuffer();

    targets[0] = new RenderTarget(WIN_WIDTH, WIN_HEIGHT, DXGI_FORMAT_R8G8B8A8_UNORM);
    targets[1] = new RenderTarget(WIN_WIDTH, WIN_HEIGHT, DXGI_FORMAT_R8G8B8A8_UNORM);

    depthStencil = new DepthStencil();

    Texture* texture = Texture::Add(L"R", targets[0]->GetSRV());

    rayleighQuad = new Quad(Vector2(200, 100));
    rayleighQuad->Pos() = { 100, 150, 0 };
    rayleighQuad->GetMaterial()->SetDiffuseMap(texture);
    rayleighQuad->UpdateWorld();

    texture = Texture::Add(L"M", targets[1]->GetSRV());
    mieQuad = new Quad(Vector2(200, 100));
    mieQuad->Pos() = { 100, 50, 0 };
    mieQuad->GetMaterial()->SetDiffuseMap(texture);
    mieQuad->UpdateWorld();

    quad = new Quad(Vector2(2, 2));
    quad->GetMaterial()->SetShader(L"Landscape/ScatteringTarget.hlsl");

    material->SetShader(L"Landscape/Scattering.hlsl");
    material->SetDiffuseMap(L"Textures/Landscape/NightSky.png");

    mesh = new Mesh<VertexUV>();
    MakeMesh();
    mesh->CreateMesh();

    depthStencilState[0] = new DepthStencilState();
    depthStencilState[1] = new DepthStencilState();
    depthStencilState[1]->DepthEnable(false);
}

Scattering::~Scattering()
{
    delete targetBuffer;

    delete targets[0];
    delete targets[1];
    delete depthStencil;

    delete rayleighQuad;
    delete mieQuad;
    delete quad;
    
    delete mesh;

    delete depthStencilState[0];
    delete depthStencilState[1];
}

void Scattering::PreRender()
{
    RenderTarget::SetMulti(targets, 2, depthStencil);

    targetBuffer->SetPS(10);

    quad->Render();
}

void Scattering::Render()
{
    DC->PSSetShaderResources(10, 1, &targets[0]->GetSRV());
    DC->PSSetShaderResources(11, 1, &targets[1]->GetSRV());

    material->Set();

    depthStencilState[1]->SetState();
    mesh->Draw();
    depthStencilState[0]->SetState();
}

void Scattering::PostRender()
{
    rayleighQuad->Render();
    mieQuad->Render();
}

void Scattering::GUIRender()
{
    ImGui::SliderInt("SampleCount", &targetBuffer->Get().sampleCount, 1, 50);
}

void Scattering::MakeMesh()
{    
    UINT latitude = stacks;
    UINT longitude = slices;

    vector<VertexUV>& vertices = mesh->GetVertices();
    vertices.reserve(latitude * longitude * 2);

    for (UINT i = 0; i < longitude; i++)
    {
        float xz = 100.0f * (i / (longitude - 1.0f)) * XM_PI / 180.0f;

        for (UINT j = 0; j < latitude; j++)
        {
            float y = XM_PI * j / (latitude - 1);

            VertexUV vertex;
            vertex.pos.x = sin(xz) * cos(y) * radius;
            vertex.pos.y = cos(xz) * radius;
            vertex.pos.z = sin(xz) * sin(y) * radius;

            vertex.uv.x = 0.5f / (float)longitude + i / (float)longitude;
            vertex.uv.y = 0.5f / (float)latitude + j / (float)latitude;

            vertices.push_back(vertex);
        }
    }

    for (UINT i = 0; i < longitude; i++)
    {
        float xz = 100.0f * (i / (longitude - 1.0f)) * XM_PI / 180.0f;

        for (UINT j = 0; j < latitude; j++)
        {
            float y = (XM_PI * 2.0f) - (XM_PI * j / (latitude - 1));

            VertexUV vertex;
            vertex.pos.x = sin(xz) * cos(y) * radius;
            vertex.pos.y = cos(xz) * radius;
            vertex.pos.z = sin(xz) * sin(y) * radius;

            vertex.uv.x = 0.5f / (float)longitude + i / (float)longitude;
            vertex.uv.y = 0.5f / (float)latitude + j / (float)latitude;

            vertices.push_back(vertex);
        }
    }

    vector<UINT>& indices = mesh->GetIndices();
    indices.reserve((latitude - 1) * (longitude - 1) * 2 * 6);

    for (UINT i = 0; i < longitude - 1; i++)
    {
        for (UINT j = 0; j < latitude - 1; j++)
        {
            indices.push_back(i * latitude + j);
            indices.push_back((i + 1) * latitude + j);
            indices.push_back((i + 1) * latitude + j + 1);

            indices.push_back((i + 1) * latitude + j + 1);            
            indices.push_back(i * latitude + j + 1);
            indices.push_back(i * latitude + j);
        }
    }

    UINT offset = latitude * longitude;
    for (UINT i = 0; i < longitude - 1; i++)
    {
        for (UINT j = 0; j < latitude - 1; j++)
        {
            indices.push_back(offset + i * latitude + j);
            indices.push_back(offset + (i + 1) * latitude + j + 1);
            indices.push_back(offset + (i + 1) * latitude + j);            
                        
            indices.push_back(offset + i * latitude + j + 1);
            indices.push_back(offset + (i + 1) * latitude + j + 1);
            indices.push_back(offset + i * latitude + j);
        }
    }
}
