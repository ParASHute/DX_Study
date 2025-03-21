#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
    terrain = new Terrain();

    /*
    trees.reserve(COUNT);
    FOR(COUNT)
    {
        Vector2 size;
        size.x = Random(3.0f, 10.0f);
        size.y = Random(3.0f, 10.0f);

        Quad* tree = new Quad(size);
        tree->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Tree.png");
        tree->Pos().x = Random(0.0f, terrain->GetSize().x);
        tree->Pos().z = Random(0.0f, terrain->GetSize().y);
        tree->Pos().y = terrain->GetHeight(tree->Pos()) + size.y * 0.5f;

        trees.push_back(tree);
    }
    */

    material = new Material(L"Geometry/Billboard.hlsl");
    material->SetDiffuseMap(L"Textures/Landscape/Tree.png");

    geometryShader = Shader::AddGS(L"Geometry/Billboard.hlsl");

    vertices.resize(COUNT);

    FOR(COUNT)
    {        
        vertices[i].uv.x = Random(3.0f, 10.0f);
        vertices[i].uv.y = Random(3.0f, 10.0f);

        vertices[i].pos.x = Random(0.0f, terrain->GetSize().x);
        vertices[i].pos.z = Random(0.0f, terrain->GetSize().y);
        vertices[i].pos.y = terrain->GetHeight(vertices[i].pos) + vertices[i].uv.y * 0.5f;
    }

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), COUNT);

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->Alpha(true);

    depthState[0] = new DepthStencilState();
    depthState[1] = new DepthStencilState();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

BillboardScene::~BillboardScene()
{
    //for (Quad* tree : trees)
        //delete tree;
    delete material;
    delete vertexBuffer;

    delete blendState[0];
    delete blendState[1];

    delete depthState[0];
    delete depthState[1];
}

void BillboardScene::Update()
{
    //for (Quad* tree : trees)
    //{
    //    //tree->Rot().x = CAM->Rot().x;
    //    //tree->Rot().y = CAM->Rot().y;
    //    Vector3 dir = tree->Pos() - CAM->Pos();
    //    tree->Rot().y = atan2(dir.x, dir.z);
    //
    //    tree->UpdateWorld();
    //}
}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
    terrain->Render();

    blendState[1]->SetState();
    depthState[1]->SetState();

    //for (Quad* tree : trees)
    //    tree->Render();

    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

    material->Set();
    geometryShader->Set();

    DC->Draw(COUNT, 0);

    DC->GSSetShader(nullptr, nullptr, 0);

    blendState[0]->SetState();
    depthState[0]->SetState();
}

void BillboardScene::PostRender()
{
}

void BillboardScene::GUIRender()
{
}