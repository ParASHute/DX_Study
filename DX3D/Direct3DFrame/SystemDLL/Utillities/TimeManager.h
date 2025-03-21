#pragma once

#include "SystemDef.h"

EXTERN class SYSTEM_DLL TimeManager
{
public:
	DECLARE_SINGLETON(TimeManager);

private:
	LARGE_INTEGER FrameTime;
	LARGE_INTEGER FixTime;
	LARGE_INTEGER LastTime;
	LARGE_INTEGER CpuTick;

	float DeltaTime;
	float TimeScale;

public:
	void InitTimeMgr();
	void SetTime();

public:
	float GetDeltaTime() const{
		return DeltaTime;
	}

	void SetTimeScale(float Scale)
	{
		TimeScale = Scale;
	}
	float GetTimeScale()
	{
		return TimeScale;
	}

public:
	TimeManager();
	~TimeManager();

};

