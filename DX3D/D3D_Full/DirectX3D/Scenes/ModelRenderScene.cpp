#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
    model = new Model("Boogeyman");     
    model->GetMesh(1)->SetMaterial(model->AddMaterial("Skin"));
    model->GetMesh(2)->SetMaterial(model->AddMaterial("Tooth"));
    model->GetMesh(3)->SetMaterial(model->AddMaterial("Eye"));
}

ModelRenderScene::~ModelRenderScene()
{
    delete model;
}

void ModelRenderScene::Update()
{
    model->UpdateWorld();
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
    model->Render();
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
    ImGui::SliderInt("Mesh", &selectMeshNum, 0, model->GetMeshNum());
    if (ImGui::Button("AddMaterial"))
    {
        model->GetMesh(selectMeshNum)->SetMaterial(model->AddMaterial());
    }

    ImGui::SameLine();

    if (ImGui::Button("SaveMaterial"))
    {
        SaveMaterial();
    }

    model->GUIRender();
}

void ModelRenderScene::SaveMaterial()
{
    string name = model->GetName();
    vector<Material*> materials = model->GetMaterials();

    string savePath = "Models/Materials/" + name + "/";    ;

    CreateFolders(savePath);    

    for (Material* material : materials)
    {
        string path = savePath + material->GetName() + ".mat";
        material->Save(path);
    }
}
