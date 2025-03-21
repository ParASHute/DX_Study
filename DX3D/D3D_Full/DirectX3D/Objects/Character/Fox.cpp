#include "Framework.h"

Fox::Fox() : ModelAnimator("Fox")
{
    ReadClip("Idle");
    ReadClip("Run", 0, "FoxTransform");

    PlayClip(curState);
}

Fox::~Fox()
{
}

void Fox::Update()
{
    Control();
    Move();
    Rotate();

    ModelAnimator::Update();
}

void Fox::Render()
{
    ModelAnimator::Render();
}

void Fox::Control()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        destPos = terrain->Picking();

        if (aStar->IsCollisionObstacle(GlobalPos(), destPos))
        {
            SetPath();
        }
        else
        {
            path.clear();
            path.push_back(destPos);
        }        
    }
}

void Fox::Move()
{
    if (path.empty())
    {
        SetState(IDLE);
        return;
    }

    SetState(RUN);

    Vector3 dest = path.back();

    Vector3 direction = dest - GlobalPos();
    direction.y = 0.0f;

    if (direction.Length() < 1.0f)
        path.pop_back();

    velocity = direction.GetNormalized();

    Pos() += velocity * moveSpeed * DELTA;
}

void Fox::Rotate()
{
    if (curState == IDLE) return;

    Vector3 forward = Forward();
    Vector3 cross = Cross(forward, velocity);

    if (cross.y < 0)
        Rot().y += rotSpeed * DELTA;
    else if(cross.y > 0)
        Rot().y -= rotSpeed * DELTA;
}

void Fox::SetState(State state)
{
    if (curState == state) return;

    curState = state;
    PlayClip(state);
}

void Fox::SetPath()
{
    int startIndex = aStar->FindCloseNode(GlobalPos());
    int endIndex = aStar->FindCloseNode(destPos);

    aStar->GetPath(startIndex, endIndex, path);
    aStar->MakeDirectPath(GlobalPos(), destPos, path);    

    UINT pathSize = path.size();

    while (path.size() > 2)
    {
        vector<Vector3> tempPath = path;
        tempPath.erase(tempPath.begin());
        tempPath.pop_back();

        Vector3 start = path.back();
        Vector3 end = path.front();

        aStar->MakeDirectPath(start, end, tempPath);
        path.clear();

        path = tempPath;
        path.insert(path.begin(), end);
        path.push_back(start);

        if (pathSize == path.size())
            break;
        else
            pathSize = path.size();
    }

    path.insert(path.begin(), destPos);
}
