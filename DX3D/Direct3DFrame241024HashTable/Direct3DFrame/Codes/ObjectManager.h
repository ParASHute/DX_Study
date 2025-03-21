#pragma once
#include "HashTable.h"
#include "GameObject.h"
class ObjectManager
{
	DECLARE_SINGLETON(ObjectManager);
public:
	ObjectManager();
	~ObjectManager();
private:
	HashTable<class GameObject*> m_Hash;
	void InsertObject(const TCHAR* pObjKey, GameObject* pObject);


};

