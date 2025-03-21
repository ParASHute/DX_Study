#pragma once
#include "framework.h"

//데이터 저장용 해시 테이블 구현
template<typename T>
struct tagDataSet
{
	const TCHAR* key;
	T Value;

	tagDataSet(const TCHAR* _key,T ValueData)
		:key(_key),Value(ValueData)
	{}
};

template<typename T>
class HashTable
{
public:
	HashTable(const int& ReserveSize)
		:m_pChainList(new list<list<tagDataSet<T>*>*>[ReserveSize]),
		m_iSize(ReserveSize)
	{

	}
	~HashTable()
	{

	}

private:
	list<list<tagDataSet<T>*>*>* m_pChainList;
	int m_iSize;

public:
	list<list<tagDataSet<T>*>*>* operator[] (int index)
	{
		return &m_pChainList[index];
	}
	int Size()
	{
		return m_iSize;
	}

	//문자를 숫자로 변환하여 배열 키값으로 쓴다.
	int Hashing(const TCHAR* key)
	{
		int Length = lstrlen(key);
		int Result = 0;
		for (int i = 0; i < Length; ++i)
		{
			Result += key[i];
		}
		//배열 사이즈 안넘게
		return Result & m_iSize;
	}
	void Insert(const TCHAR* key, T Value)
	{
		tagDataSet<T>* pDataSet = new tagDataSet<T>(key,Value);
		int index = Hashing(key);

		//해당 인덱스에 리스트가 없으면
		if (m_pChainList[index].empty())
		{
			//리스트 생성해서 추가 해줌.
			list<tagDataSet<T>*>* InnerList = new list<tagDataSet<T>*>;
			InnerList->push_back(pDataSet);
			m_pChainList[index].push_back(InnerList);
		}
		else
		{
			//겹치는 인덱스가 있으면 그안에 리스트에서 해당 키에 맞는 리스트에 넣어준다.
			for (typename list<list<tagDataSet<T>*>*>::iterator iter = m_pChainList[index].begin();
				iter != m_pChainList[index].end(); ++iter)
			{			
				if (key == (*iter)->front()->key)
				{
					(*iter)->push_back(pDataSet);
					return;
				}
			}

			list<tagDataSet<T>*>* InnerList = new list<tagDataSet<T>*>;
			InnerList->push_back(pDataSet);
			m_pChainList[index].push_back(InnerList);
		}
	}

	//전체 순회 하면서 삭제
	void Release()
	{
		for (int i = 0; i < m_iSize; ++i)
		{
			for (typename list<list<tagDataSet<T>*>*>::iterator iter = m_pChainList[i].begin();
				iter != m_pChainList[i].end(); ++iter)
			{
				for (typename list<tagDataSet<T>*>::iterator iter1 = (*iter)->begin();
					iter1 != (*iter)->end(); ++iter1)
				{
					SAFE_DELETE((*iter1)->Value);
					SAFE_DELETE((*iter1));
				}
				(*iter)->clear();
				SAFE_DELETE((*iter));
			}
		}
		SAFE_DELETE_ARRAY(m_pChainList);
	}

	//검색
	const T Find(const TCHAR* Key, const int& Cnt = 0)
	{
		int iKey = Hashing(Key);

		for (typename list<list<tagDataSet<T>*>*>::iterator iter = m_pChainList[Key].begin();
			iter != m_pChainList[Key].end(); ++iter)
		{
			if (!lstrcmp((*iter)->front()->key,Key))
			{
				typename list<tagDataSet<T>*>::iterator iter1 = (*iter)->begin();

				for (int i = 0; i < Cnt; ++i)
				{
					++iter1;
				}
				return (*iter)->Value;
			}
		}
		return NULL;
	}

};
