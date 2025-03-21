#pragma once

//씬을 구성하는 부모 오브젝트.
//언리얼에서 Map,Level
class SceneObject
{
public:

	virtual HRESULT Initiallize() PURE;
	virtual void Update() PURE;

	virtual void PreRender() PURE;
	virtual void Render() PURE;
	virtual void PostRender() PURE;
	virtual void GUIRender() PURE;
	virtual void Release() PURE;
public:
	SceneObject();
	virtual ~SceneObject();

};

