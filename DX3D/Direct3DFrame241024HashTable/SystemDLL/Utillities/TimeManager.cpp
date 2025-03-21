#include "..\Utillities\TimeManager.h"
TimeManager::TimeManager()
	:DeltaTime(0.f),TimeScale(1.f)
{
	InitTimeMgr();
}

TimeManager::~TimeManager()
{
}



void TimeManager::InitTimeMgr()
{
	//현재 cpu 진동수를 반환하는 함수
	QueryPerformanceCounter(&FrameTime);
	QueryPerformanceCounter(&FixTime);
	QueryPerformanceCounter(&LastTime);

	//1초동안 cpu진동수(연산수) 반환
	QueryPerformanceFrequency(&CpuTick);
}

void TimeManager::SetTime()
{
	//현재 프레임 시간
	QueryPerformanceCounter(&FrameTime);

	//cpu 시간마다 cpu 속도 갱신.
	if (FrameTime.QuadPart - LastTime.QuadPart > CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&CpuTick);
		LastTime.QuadPart = FrameTime.QuadPart;
	}

	//현재 시간 - 이전 시간 / 초당 cpu연산량 -> 1프레임에 걸린 초당 연산 시간
	DeltaTime = float(FrameTime.QuadPart - FixTime.QuadPart) / CpuTick.QuadPart;
	DeltaTime *= TimeScale; //시간 변경용

	FixTime = FrameTime;//이전 프레임 저장
}

