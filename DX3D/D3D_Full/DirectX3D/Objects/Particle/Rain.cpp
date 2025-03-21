#include "Framework.h"

Rain::Rain()
{
    material->SetShader(L"Geometry/Rain.hlsl");
    material->SetDiffuseMap(L"Textures/Effect/Rain.png");

    geometryShader = Shader::AddGS(L"Geometry/Rain.hlsl");

    buffer = new WeatherBuffer();    

    Create();
}

Rain::~Rain()
{
    delete buffer;
}

void Rain::Update()
{
    buffer->Get().time += DELTA;
}

void Rain::Render()
{
    buffer->SetVS(10);
    Particle::Render();
}

void Rain::GUIRender()
{
    ImGui::Text("Rain Option");
    ImGui::DragFloat3("Velocity", (float*)&buffer->Get().velocity, 0.1f);
    ImGui::SliderFloat("Distance", &buffer->Get().distance, 0.0f, 500.0f);
    ImGui::DragFloat3("Origin", (float*)&buffer->Get().origin, 0.1f);
    ImGui::DragFloat3("Size", (float*)&buffer->Get().size, 0.1f);

    ImGui::ColorEdit4("Color", (float*)&buffer->Get().color);
}

void Rain::Create()
{
    particleCount = MAX_COUNT;

    vertices.resize(particleCount);

    FOR(particleCount)
    {
        Float2 size;
        size.x = Random(0.1f, 0.4f);
        size.y = Random(4.0f, 8.0f);

        Float3 pos;
        pos.x = Random(-buffer->Get().size.x, buffer->Get().size.x);
        pos.y = Random(-buffer->Get().size.y, buffer->Get().size.y);
        pos.z = Random(-buffer->Get().size.z, buffer->Get().size.z);

        vertices[i].pos = pos;
        vertices[i].uv = size;
    }

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), particleCount);
}
