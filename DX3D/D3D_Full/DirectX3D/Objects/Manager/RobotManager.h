#pragma once

class RobotManager : public Singleton<RobotManager>
{
private:
    const UINT SIZE = 30;
    const float SPAWN_TIME = 2.0f;

public:
    RobotManager();
    ~RobotManager();

    void Update();
    void Render();
    void PostRender();

    void SetTarget(Transform* target);

    bool IsCollision(Ray ray, Vector3& hitPoint);

private:
    void Collision();
    void Spawn();

private:
    ModelAnimatorInstancing* robotInstancing;
    vector<Robot*> robots;

    Transform* target;

    float time = 0.0f;
};