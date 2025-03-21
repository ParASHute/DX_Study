#pragma once

#define DECLARE_SINGLETON(type)public:		\
	static type** GetInstance(void)			\
	{										\
		static type* pInstance = new type;	\
		if(pInstance == NULL)				\
			pInstance = new type;			\
			return &pInstance;				\
	}										\
	static void DestroyInstance(void)		\
	{										\
		type** ppInstance = GetInstance();	\
		if(*ppInstance != NULL)				\
		{									\
			delete *ppInstance;				\
			*ppInstance = NULL;				\
		}									\
	}

#define GET_SINGLE(type) (*(type::GetInstance()))


#define Check(hr) {assert(SUCCEEDED(hr));}
#define MSGBOX(str) MessageBox(NULL,str,L"Message",MB_OK)

//포인터 삭제 관련 코드

//Release 함수가 있는 객체들은 이걸 사용 d3d쪽은 객체는 대부분 있음
#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p) {if(p) {delete p; (p)=NULL; } } //삭제하고 NULL

//부모 클래스 super로 호출 가능하도록
//Static 변수로 클래스마다 만들어서 해당 주소를 고유 넘버로 사용
#define GENERATED_BODY(type)public:		\
using Super = type;						\
static UClass StaticClass()				\
{										\
	static int Private = 0;				\
	return (UClass)&Private;			\
}										\