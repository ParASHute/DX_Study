#include "framework.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
	:m_Hash(20)
{
}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::InsertObject(const TCHAR* pObjKey, GameObject* pObject)
{
	m_Hash.Insert(pObjKey, pObject);
}
