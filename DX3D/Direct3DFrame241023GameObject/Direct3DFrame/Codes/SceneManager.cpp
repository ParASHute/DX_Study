#include "framework.h"
#include "SceneManager.h"

#include "Stage.h" //사용할 씬


SceneManager::SceneManager()
	:CurrentScene(NULL) //포인터 초기화
{
}

SceneManager::~SceneManager()
{
	Release();
}


HRESULT SceneManager::Initiallize(STATEID ID)
{
	//현재 씬이 있으면 삭제
	SAFE_DELETE(CurrentScene);

	//enum 값에 맞춰서 씬 생성 일단 하나만있으므로 stage만 구성
	switch (ID)
	{
	/*case STATEID_LOGO:

		break;*/
	case STATEID_STAGE:
		CurrentScene = new Stage(); 
		break;

	default:
		break;
	}

	if (FAILED(CurrentScene->Initiallize()))
	{
		MSGBOX(L"GameScene Create Failed");
		return E_FAIL;
	}

	return S_OK;
}

void SceneManager::Update()
{
	CurrentScene->Update();
}

void SceneManager::PreRender()
{
	CurrentScene->PreRender();
}

void SceneManager::Render()
{
	CurrentScene->Render();
}

void SceneManager::PostRender()
{
	CurrentScene->PostRender();
}

void SceneManager::GUIRender()
{
	CurrentScene->GUIRender();
}

void SceneManager::Release()
{
	SAFE_DELETE(CurrentScene);
}

