#pragma once
#include "SceneObject.h"

//기본 씬을 구성할 코드를 여기 넣는다.
class Stage : public SceneObject
{
public:
	virtual HRESULT Initiallize();
	virtual void Update();

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual void GUIRender();
	virtual void Release();
public:
	Stage();
	~Stage();
};

