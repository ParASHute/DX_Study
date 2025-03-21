#pragma once

class Scattering : public GameObject
{
private:
    class TargetBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Float3 waveLength = Float3(0.65f, 0.57f, 0.475f);
            int sampleCount = 5;

            Float3 invWaveLength;
            float padding;
        };
    public:
        TargetBuffer() : ConstBuffer(&data, sizeof(Data))
        {
            data.invWaveLength.x = 1.0f / pow(data.waveLength.x, 4.0f);
            data.invWaveLength.y = 1.0f / pow(data.waveLength.y, 4.0f);
            data.invWaveLength.z = 1.0f / pow(data.waveLength.z, 4.0f);

            //data.waveLength.x = pow(data.waveLength.x, 0.84f);
            //data.waveLength.y = pow(data.waveLength.y, 0.84f);
            //data.waveLength.z = pow(data.waveLength.z, 0.84f);
        }

        Data& Get() { return data; }

    private:
        Data data;
    };

public:
    Scattering();
    ~Scattering();

    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

private:
    void MakeMesh();

private:
    TargetBuffer* targetBuffer;

    RenderTarget* targets[2];
    DepthStencil* depthStencil;

    Quad* rayleighQuad;
    Quad* mieQuad;

    Quad* quad;

    //Sphere
    float radius = 1;
    UINT slices = 32, stacks = 32;

    Mesh<VertexUV>* mesh;

    DepthStencilState* depthStencilState[2];
};