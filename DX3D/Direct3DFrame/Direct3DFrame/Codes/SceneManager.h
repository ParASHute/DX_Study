#pragma once

//전체 씬을 관리할 매니저 클래스.
class SceneManager
{
	//싱글톤으로 만든다.
	DECLARE_SINGLETON(SceneManager);
private:
	//포인터라 파일 Include 안해줘도 됨.
	class SceneObject* CurrentScene; //현재 장면을 포인터로 담아놓는다.
public:

	virtual HRESULT Initiallize(STATEID ID);
	virtual void Update();

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual void GUIRender();
	virtual void Release();

public:
	SceneManager();
	~SceneManager();
	
};

