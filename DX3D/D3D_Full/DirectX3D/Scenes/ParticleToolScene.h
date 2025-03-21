#pragma once

class ParticleToolScene : public Scene
{
private:
    const UINT MAX_COUNT = 1000;

    struct InstanceData
    {
        Matrix transform = XMMatrixIdentity();        
    };

    struct ParticleData
    {
        bool isLoop = true;
        bool isAdditive = true;
        bool isBillboard = true;
        UINT count = 100;
        float duration = 1.0f;
        Vector3 minVelocity = { -1, -1, -1 };
        Vector3 maxVelocity = { +1, +1, +1 };
        Vector3 minAccelation;
        Vector3 maxAccelation;
        Vector3 minStartScale = { 1, 1, 1 };
        Vector3 maxStartScale = { 1, 1, 1 };
        Vector3 minEndScale = { 1, 1, 1 };
        Vector3 maxEndScale = { 1, 1, 1 };
        float minSpeed = 1.0f;
        float maxSpeed = 3.0f;
        float minAngularVelocity = -10.0f;
        float maxAngularVelocity = +10.0f;
        float minStartTime = 0.0f;
        float maxStartTime = 0.0f;        
        Float4 startColor = { 1, 1, 1, 1 };
        Float4 endColor = { 1, 1, 1, 1 };
    };

    struct ParticleInfo
    {
        Transform transform;
        Vector3 velocity;
        Vector3 accelation;
        Vector3 startScale;
        Vector3 endScale;

        float speed = 1.0f;
        float angularVelocity = 0.0f;
        float startTime = 0.0f;
    };

public:
    ParticleToolScene();
    ~ParticleToolScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;    

private:
    void UpdatePhysical();
    void UpdateColor();

    void Init();

    void Save(string file);
    void Load(string file);

    void EditTexture();
    void SaveDialog();
    void LoadDialog();

private:    
    Quad* quad;

    vector<InstanceData> instances;
    vector<ParticleInfo> particleInfos;    

    VertexBuffer* instanceBuffer;

    ParticleData data;

    float lifeTime = 0.0f;
    UINT drawCount = 0; 
    UINT particleCount = 100;

    BlendState* blendState[2];
    DepthStencilState* depthState[2];

    string projectPath;
};