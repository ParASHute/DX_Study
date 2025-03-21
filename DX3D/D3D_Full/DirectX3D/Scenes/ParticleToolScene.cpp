#include "Framework.h"
#include "ParticleToolScene.h"

ParticleToolScene::ParticleToolScene()
{
    quad = new Quad(Vector2(1, 1));
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl");
    quad->GetMaterial()->SetDiffuseMap(L"Textures/Effect/Snow.png");

    instances.resize(MAX_COUNT);
    particleInfos.resize(MAX_COUNT);

    instanceBuffer = new VertexBuffer(instances.data(),
        sizeof(InstanceData), MAX_COUNT);

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->Alpha(true);

    depthState[0] = new DepthStencilState();
    depthState[1] = new DepthStencilState();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

    char path[128];
    GetCurrentDirectoryA(sizeof(path), path);
    projectPath = path;

    Init();
}

ParticleToolScene::~ParticleToolScene()
{
    delete quad;
    delete instanceBuffer;

    delete blendState[0];
    delete blendState[1];

    delete depthState[0];
    delete depthState[1];
}

void ParticleToolScene::Update()
{
    lifeTime += DELTA;

    UpdatePhysical();
    UpdateColor();
    quad->UpdateWorld();

    if (lifeTime > data.duration)
    {
        Init();
    }
}

void ParticleToolScene::PreRender()
{
}

void ParticleToolScene::Render()
{
    instanceBuffer->Set(1);

    quad->SetRender();

    blendState[1]->SetState();
    depthState[1]->SetState();

    DC->DrawIndexedInstanced(6, drawCount, 0, 0, 0);
}

void ParticleToolScene::PostRender()
{
}

void ParticleToolScene::GUIRender()
{
    ImGui::Text("Particle Editor");
    EditTexture();

    ImGui::Checkbox("Loop", &data.isLoop);
    ImGui::Checkbox("Additive", &data.isAdditive);
    ImGui::Checkbox("Billboard", &data.isBillboard);
    ImGui::SliderInt("ParticleCount", (int*)&particleCount, 1, MAX_COUNT);
    ImGui::DragFloat("Duration", &data.duration, 0.1f, 10.0f);
    ImGui::ColorEdit4("StartColor", (float*)&data.startColor);
    ImGui::ColorEdit4("EndColor", (float*)&data.endColor);
    ImGui::SliderFloat3("MinVelocity", (float*)&data.minVelocity, -1, 1);
    ImGui::SliderFloat3("MaxVelocity", (float*)&data.maxVelocity, -1, 1);
    ImGui::SliderFloat3("MinAccelation", (float*)&data.minAccelation, -5, 5);
    ImGui::SliderFloat3("MaxAccelation", (float*)&data.maxAccelation, -5, 5);
    ImGui::SliderFloat3("MinStartScale", (float*)&data.minStartScale, 0, 5);
    ImGui::SliderFloat3("MaxStartScale", (float*)&data.maxStartScale, 0, 5);
    ImGui::SliderFloat3("MinEndScale", (float*)&data.minEndScale, 0, 5);
    ImGui::SliderFloat3("MaxEndScale", (float*)&data.maxEndScale, 0, 5);
    ImGui::SliderFloat("MinAngularVelocity", (float*)&data.minAngularVelocity, -10, 10);
    ImGui::SliderFloat("MaxAngularVelocity", (float*)&data.maxAngularVelocity, -10, 10);
    ImGui::SliderFloat("MinSpeed", (float*)&data.minSpeed, 0, data.maxSpeed);
    ImGui::SliderFloat("MaxSpeed", (float*)&data.maxSpeed, data.minSpeed, 200);
    ImGui::SliderFloat("MinStartTime", (float*)&data.minStartTime, 0.0f, data.maxStartTime);
    ImGui::SliderFloat("MaxStartTime", (float*)&data.maxStartTime, data.minStartTime, data.duration);    

    SaveDialog();
    ImGui::SameLine();
    LoadDialog();
}

void ParticleToolScene::UpdatePhysical()
{
    drawCount = 0;

    FOR(data.count)
    {
        if (particleInfos[i].startTime > lifeTime) continue;

        particleInfos[i].velocity += particleInfos[i].accelation * DELTA;
        particleInfos[i].transform.Pos() += particleInfos[i].velocity * particleInfos[i].speed * DELTA;
        particleInfos[i].transform.Rot().z += particleInfos[i].angularVelocity * DELTA;        
        if (data.isBillboard)
        {
            particleInfos[i].transform.Rot().x = CAM->Rot().x;
            particleInfos[i].transform.Rot().y = CAM->Rot().y;
        }

        float t = (lifeTime - particleInfos[i].startTime)
            / (data.duration - particleInfos[i].startTime);

        particleInfos[i].transform.Scale() =
            Lerp(particleInfos[i].startScale, particleInfos[i].endScale, t);

        particleInfos[i].transform.UpdateWorld();
        instances[drawCount++].transform =
            XMMatrixTranspose(particleInfos[i].transform.GetWorld());
    }

    instanceBuffer->Update(instances.data(), drawCount);
}

void ParticleToolScene::UpdateColor()
{
    float t = lifeTime / data.duration;

    Float4 color;
    color.x = Lerp(data.startColor.x, data.endColor.x, t);
    color.y = Lerp(data.startColor.y, data.endColor.y, t);
    color.z = Lerp(data.startColor.z, data.endColor.z, t);
    color.w = Lerp(data.startColor.w, data.endColor.w, t);

    quad->GetMaterial()->GetData().diffuse = color;
}

void ParticleToolScene::Init()
{
    if (data.isAdditive)
        blendState[1]->Additive();
    else
        blendState[1]->Alpha(true);

    lifeTime = 0.0f;
    drawCount = 0;
    data.count = particleCount;

    instances.resize(data.count);
    particleInfos.resize(data.count);    

    for (ParticleInfo& info : particleInfos)
    {
        info.transform.Pos() = {};        

        info.velocity = Random(data.minVelocity, data.maxVelocity);        
        info.accelation = Random(data.minAccelation, data.maxAccelation);
        info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        info.speed = Random(data.minSpeed, data.maxSpeed);
        info.startTime = Random(data.minStartTime, data.maxStartTime);
        info.startScale = Random(data.minStartScale, data.maxStartScale);
        info.endScale = Random(data.minEndScale, data.maxEndScale);
        info.velocity.Normalize();
    }    
}

void ParticleToolScene::Save(string file)
{
    BinaryWriter* writer = new BinaryWriter(file);

    writer->WString(quad->GetMaterial()->GetDiffuseMap()->GetFile());

    writer->Byte(&data, sizeof(ParticleData));

    delete writer;
}

void ParticleToolScene::Load(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    wstring textureFile = reader->WString();
    quad->GetMaterial()->SetDiffuseMap(textureFile);

    ParticleData* particleData = new ParticleData();
    reader->Byte((void**)&particleData, sizeof(ParticleData));

    data = *particleData;

    UINT temp = data.count;
    data.count = particleCount;
    particleCount = temp;

    delete reader;
}

void ParticleToolScene::EditTexture()
{
    ImTextureID textureID = quad->GetMaterial()->GetDiffuseMap()->GetSRV();

    if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
    {
        DIALOG->OpenDialog("SelectTexture", "SelectTexture", ".png, .jpg, .tga", ".");
    }

    if (DIALOG->Display("SelectTexture"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();
            file = file.substr(projectPath.size() + 1, file.size());

            quad->GetMaterial()->SetDiffuseMap(ToWString(file));
        }

        DIALOG->Close();
    }
}

void ParticleToolScene::SaveDialog()
{
    if (ImGui::Button("Save"))
    {
        DIALOG->OpenDialog("Save", "Save", ".fx", ".");
    }

    if (DIALOG->Display("Save"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();
            file = file.substr(projectPath.size() + 1, file.size());

            Save(file);
        }

        DIALOG->Close();
    }
}

void ParticleToolScene::LoadDialog()
{
    if (ImGui::Button("Load"))
    {
        DIALOG->OpenDialog("Load", "Load", ".fx", ".");
    }

    if (DIALOG->Display("Load"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();
            file = file.substr(projectPath.size() + 1, file.size());

            Load(file);
        }

        DIALOG->Close();
    }
}