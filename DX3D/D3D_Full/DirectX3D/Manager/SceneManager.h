#pragma once

class SceneManager : public Singleton<SceneManager>
{
public:
    SceneManager();
    ~SceneManager();

    void Update();

    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

    void Create(string key, Scene* scene);
       
    Scene* Add(string key);
    void Remove(string key);
private:
    void AddScene();
    void RemoveScene();

private:
    map<string, Scene*> scenes;

    list<Scene*> curScenes;

    vector<string> addScenes, removeScenes;
};