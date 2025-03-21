
#include "framework.h"
#include "MainApp.h"
#include "SceneManager.h"

MainApp::MainApp(void)
{
}

MainApp::~MainApp(void)
{
}


HRESULT MainApp::InitApp(void)
{
	if (FAILED(DEVICE_SYSTEM::InitDevice(WINMODE_WIN, g_hWnd, STARTWINSIZEX, STARTWINSIZEY)))
	{
		MSGBOX(L"디바이스 초기화 실패");
		return E_FAIL;
	}
	g_WindowSizeX = STARTWINSIZEX;
	g_WindowSizeY = STARTWINSIZEY;

	if (GET_SINGLE(SceneManager)->Initiallize(STATEID_STAGE))
	{
		return E_FAIL;
	}

	//로드
	XFONT::AddColor("white",1,1,1);
	XFONT::AddStyle("Default",L"궁서");
	//로드

	//세팅
	XFONT::SetColor("white");
	XFONT::SetStyle("Default");
	//세팅
	return S_OK;
}

void MainApp::Update(void)
{
	
	XTIMER::SetTime(); //시간 계산
	GET_SINGLE(SceneManager)->Update();
}

void MainApp::Render(void)
{
	DEVICE_SYSTEM::Clear();

	XFONT::BeginDraw();

	GET_SINGLE(SceneManager)->Render();


	FPSPrint();
	XFONT::EndDraw();
	DEVICE_SYSTEM::Present();

}

void MainApp::Release(void)
{
	GET_SINGLE(SceneManager)->DestroyInstance();
	DEVICE_SYSTEM::System_Release();
}

void MainApp::FPSPrint()
{
	static int FrameCount = 0;
	++FrameCount;//계산용 프레임 카운트 1프레임마다 증가

	static float Time = 0.f;
	Time += XTIMER::GetDeltaTime();	//시간 누적

	static string fps;
	//누적 시킨 프레임 카운트를 1초 간격으로 출력
	if (Time > 1.f)
	{
		fps = "FPS : " + to_string(FrameCount);
		FrameCount = 0;
		Time = 0;
	}

	XFONT::RenderText(fps, { 150.f ,10.f });
}

