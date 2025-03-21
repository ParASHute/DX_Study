#include "Framework.h"

RobotManager::RobotManager()
{
    robotInstancing = new ModelAnimatorInstancing("Robot");
    robotInstancing->ReadClip("StandUp");
    robotInstancing->ReadClip("Walk");
    robotInstancing->ReadClip("Run");    
    robotInstancing->ReadClip("Hit");
    robotInstancing->ReadClip("Dying");

    robots.reserve(SIZE);
    FOR(SIZE)
    {
        Transform* transform = robotInstancing->Add();
        transform->SetActive(false);
        Robot* robot = new Robot(transform, robotInstancing, i);        
        robots.push_back(robot);
    }
}

RobotManager::~RobotManager()
{
    delete robotInstancing;

    for (Robot* robot : robots)
        delete robot;
}

void RobotManager::Update()
{
    Collision();

    time += DELTA;

    if (time > SPAWN_TIME)
    {
        time -= SPAWN_TIME;
        Spawn();
    }


    robotInstancing->Update();

    for (Robot* robot : robots)
        robot->Update();
}

void RobotManager::Render()
{
    robotInstancing->Render();

    for (Robot* robot : robots)
        robot->Render();
}

void RobotManager::PostRender()
{
    for (Robot* robot : robots)
        robot->PostRender();
}

void RobotManager::SetTarget(Transform* target)
{
    this->target = target;

    for (Robot* robot : robots)
        robot->SetTarget(target);
}

bool RobotManager::IsCollision(Ray ray, Vector3& hitPoint)
{
    Contact contact;
    float minDistance = FLT_MAX;    

    for (Robot* robot : robots)
    {        
        if (robot->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance)
            {
                minDistance = contact.distance;
                hitPoint = contact.hitPoint;
            }            
        }
    }

    return minDistance != FLT_MAX;
}

void RobotManager::Collision()
{
    for (Robot* robot : robots)
    {
        if (KunaiManager::Get()->IsCollision(robot->GetCollider()))
        {
            robot->Hit();
            return;
        }
    }
}

void RobotManager::Spawn()
{
    Vector3 dir;
    dir.x = Random(-1.0f, 1.0f);
    dir.z = Random(-1.0f, 1.0f);

    Vector3 randomPos = target->Pos() + dir.GetNormalized() * 1500.0f;

    for (Robot* robot : robots)
    {
        if (!robot->GetTransform()->Active())
        {
            robot->Spawn(randomPos);
            break;
        }
    }
}
