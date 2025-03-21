#pragma once
class Component
{
public: using UClass = size_t;
private:
	GENERATED_BODY(Component);

	class GameObject* gameobject;
public:
	void SetGameObject(GameObject* _gameobject)
	{
		gameobject = _gameobject;
		IsTop = true;
	}
public:
	Component();
	~Component();

public:
	virtual HRESULT Start() PURE;
	virtual void Release() PURE;

	virtual void Update() PURE;
	virtual void PreRender() PURE;
	virtual void Render() PURE;
	virtual void PostRender() PURE;
	virtual void GUIRender() PURE;

	virtual void Save();
	virtual void Load();

public:
	bool IsTop;

};

