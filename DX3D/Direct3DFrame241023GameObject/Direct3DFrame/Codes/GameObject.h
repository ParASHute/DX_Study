#pragma once
#include "Component.h"
//게임에서 사용하는 오브젝트 기본형
//컴포넌트를 추가하여 기능 추가
class GameObject
{
//size_t 자료형 이름을 Uclass로 변경
//고유한 클래스 번호로 자료형으로 사용
public: using UClass = size_t;
private:
	string objectKey; //오브젝트 구분용 이름
public:
	string GetOjbectKey() { return objectKey; }
	void SetObjectKey(const TCHAR* ptsz)
	{
		std::wstring wstr = ptsz; //wide string으로 바꿈
		std::string str(wstr.begin(), wstr.end()); //스트링으로 변환
		objectKey = str;
	}

private:
	//컴포넌트 여러개 담아놓을 맵
	map<Component::UClass, Component*> components;
public:
	template <class T>
	T* AddComponent()
	{
		//템플릿으로 컴포넌트 생성 후
		auto component = new T;
		//컴포넌트 클래스의 고유 번호를 키 값으로 잡아서 map에 넣어줌
		components.insert(make_pair(T::StaticClass(), component));
		component->SetGameObject(this); //컴포넌트 생성한 게임오브젝트 넣어준다.
		component->Start();
		return component;
	}
	template <class T>
	T* GetComponent()
	{
		auto it = components.find(T::StaticClass());
		if (it != components.end()) //찾았으면 ,못찾으면 end값임
		{
			//해당 형식인것이 명확하므로 static_cast
			return static_cast<T*>(it->second);
		}
		return nullptr;

	}

public:
	GameObject();
	~GameObject();

	virtual HRESULT Start(void);
	virtual void Release(void);

	virtual void Update(void);
	virtual void PreRender(void);
	virtual void Render(void);
	virtual void PostRender(void);
	virtual void GUIRender(void);
	

};

