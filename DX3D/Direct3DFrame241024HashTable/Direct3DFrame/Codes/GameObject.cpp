#include "framework.h"
#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	//오브젝트 삭제시 담당 컴포넌트 다 지움.
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		SAFE_DELETE(it->second);
	}

	components.clear();
}

HRESULT GameObject::Start(void)
{
	return E_NOTIMPL;
}

void GameObject::Release(void)
{
}

void GameObject::Update(void)
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		it->second->Update();
	}
}

void GameObject::PreRender(void)
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		it->second->PreRender();
	}
}

void GameObject::Render(void)
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		it->second->Render();
	}
}

void GameObject::PostRender(void)
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		it->second->PostRender();
	}
}

void GameObject::GUIRender(void)
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		it->second->GUIRender();
	}
}
