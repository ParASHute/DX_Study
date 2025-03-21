#include "Framework.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    //for (pair<string, Scene*> scene : scenes)
    for (auto scene : scenes)
        delete scene.second;
}

void SceneManager::Update()
{
    for (Scene* scene : curScenes)
        scene->Update();

    if (addScenes.size() > 0)
    {
        AddScene();        
    }

    if (removeScenes.size() > 0)
    {
        RemoveScene();        
    }
}

void SceneManager::PreRender()
{
    for (Scene* scene : curScenes)
        scene->PreRender();
}

void SceneManager::Render()
{
    for (Scene* scene : curScenes)
        scene->Render();
}

void SceneManager::PostRender()
{
    for (Scene* scene : curScenes)
        scene->PostRender();
}

void SceneManager::GUIRender()
{
    for (Scene* scene : curScenes)
        scene->GUIRender();
}

void SceneManager::Create(string key, Scene* scene)
{
    if (scenes.count(key) > 0)
        return;

    scenes[key] = scene;
}

Scene* SceneManager::Add(string key)
{
    if (scenes.count(key) == 0)
        return nullptr;

    addScenes.push_back(key);

    return scenes[key];
}

void SceneManager::Remove(string key)
{
    if (scenes.count(key) == 0)
        return;

    removeScenes.push_back(key);
}

void SceneManager::AddScene()
{   
    for (string scene : addScenes)
    {
        list<Scene*>::iterator findScene = find(curScenes.begin(), curScenes.end(), scenes[scene]);

        if (findScene != curScenes.end())
            continue;

        curScenes.push_back(scenes[scene]);
        curScenes.back()->Start();
    }    

    addScenes.clear();
}

void SceneManager::RemoveScene()
{ 
    for (string scene : removeScenes)
    {
        list<Scene*>::iterator findScene = find(curScenes.begin(), curScenes.end(), scenes[scene]);

        if (findScene == curScenes.end())
            continue;

        scenes[scene]->End();
        curScenes.erase(findScene);
    }
    
    removeScenes.clear();
}
