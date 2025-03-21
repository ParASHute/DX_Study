#include "Framework.h"

Robot::Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    : transform(transform), instancing(instancing), index(index)
{
    root = new Transform();

    collider = new CapsuleCollider(30, 100);
    //collider = new CapsuleCollider();
    collider->SetParent(root);
    collider->Rot().z = XM_PIDIV2 - 0.2f;
    collider->Pos() = { -15.0f,  10.0f, 0.0f };
    collider->SetActive(false);

    motion = instancing->GetMotion(index);
    totalEvent.resize(instancing->GetClipSize());    
    eventIters.resize(instancing->GetClipSize());    

    SetEvent(STAND_UP, bind(&Robot::EndStandUp, this), 0.7f);    
    SetEvent(HIT, bind(&Robot::EndHit, this), 0.9f);
    SetEvent(DYING, bind(&Robot::EndDying, this), 0.9f);

    FOR(totalEvent.size())
    {
        eventIters[i] = totalEvent[i].begin();
    }

    hpBar = new ProgressBar(L"Textures/UI/hp_bar.png",
        L"Textures/UI/hp_bar_BG.png");    
}

Robot::~Robot()
{
    delete collider;
    delete root;
    delete hpBar;
}

void Robot::Update()
{
    if (!transform->Active()) return;

    velocity = target->GlobalPos() - transform->GlobalPos();

    ExcuteEvent();
    Move();
    UpdateHpBar();

    root->SetWorld(instancing->GetTransformByNode(index, 3));
    collider->UpdateWorld();  
}

void Robot::Render()
{
    collider->Render();
}

void Robot::PostRender()
{
    if (!CAM->ContainPoint(barPos)) return;

    hpBar->Render();
}

void Robot::SetEvent(int clip, Event event, float timeRatio)
{
    if (totalEvent[clip].count(timeRatio) > 0)
        return;

    totalEvent[clip][timeRatio] = event;
}

void Robot::ExcuteEvent()
{
    int index = curState;

    if (totalEvent[index].empty()) return;
    if (eventIters[index] == totalEvent[index].end()) return;

    float ratio = motion->runningTime / motion->duration;

    if (eventIters[index]->first > ratio) return;

    eventIters[index]->second();
    eventIters[index]++;
}

void Robot::EndStandUp()
{
    collider->SetActive(true);

    SetState(WALK);
}

void Robot::EndHit()
{
    SetState(WALK);
}

void Robot::EndDying()
{
    transform->SetActive(false);    
    collider->SetActive(false);
}

void Robot::Hit()
{
    Audio::Get()->Play("hit", transform->Pos(), 5.0f);

    curHp -= 10.0f;
    hpBar->SetAmount(curHp / maxHp);

    if (curHp <= 0.0f)
    {
        SetState(DYING);
        return;
    }

    curState = HIT;
    instancing->PlayClip(index, HIT);
    eventIters[HIT] = totalEvent[HIT].begin();        
}

void Robot::Spawn(Vector3 pos)
{
    transform->SetActive(true);
    collider->SetActive(true);

    SetState(WALK);

    curHp = maxHp;

    transform->Pos() = pos;
        
    Audio::Get()->Play("move", transform->Pos());
}

void Robot::SetState(State state)
{
    if (curState == state) return;

    curState = state;
    instancing->PlayClip(index, state);
    eventIters[state] = totalEvent[state].begin();
}

void Robot::Move()
{
    if (curState == STAND_UP) return;
    if (curState == HIT) return;
    if (curState == DYING) return;
    if (velocity.Length() < 500.0f) return;    

    if (velocity.Length() < 1000.0f)
    {
        speed = 100.0f;

        if (curState != RUN)
        {   
            Audio::Get()->Play("pain", transform->Pos());
        }
        SetState(RUN);
    }
    else
    {
        speed = 50.0f;
        SetState(WALK);
    }

    transform->Pos() += velocity.GetNormalized() * speed * DELTA;
    transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
}

void Robot::UpdateHpBar()
{
    barPos = transform->Pos() + Vector3(0, 180.0f, 0);    

    hpBar->Pos() = CAM->WorldToScreen(barPos);
    float scale = 100.0f / velocity.Length();
    scale = Clamp(0.1f, 1.0f, scale);
    hpBar->Scale() = { scale, scale, scale };
    hpBar->UpdateWorld();
}
