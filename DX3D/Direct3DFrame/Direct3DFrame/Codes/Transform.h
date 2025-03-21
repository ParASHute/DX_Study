#pragma once
#include "Component.h"
class Transform :
    public Component
{
	GENERATED_BODY(Component);


public:
	Transform();
	~Transform();

public:
	virtual HRESULT Start() override;
	virtual void Release() override;

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

	virtual void Save();
	virtual void Load();
protected:
	Vector4

};

