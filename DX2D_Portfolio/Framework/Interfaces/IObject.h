#pragma once

class IObject
{
public:
	virtual void Init()			= 0; 
	virtual void Destroy()		= 0;	// 소멸자 대체

	virtual void Update()		= 0; 
	
	virtual void Render()		= 0;
	virtual void PostRender()	= 0;	// 후처리가 필요한 코드를 처리
	
	virtual void GUI()			= 0;	// 외부 라이브러리
};