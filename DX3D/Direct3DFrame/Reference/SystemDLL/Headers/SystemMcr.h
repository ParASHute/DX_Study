#ifndef _SYSTEMMCR_H
#define _SYSTEMMCR_H

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

#endif